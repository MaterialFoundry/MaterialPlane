/**
 * Module name: Material Plane
 * Github repository: https://github.com/CDeenen/MaterialPlane
 * Author: C Deenen (Cris#6864 on Discord)
 * 
 * Useful reference material:
 * Websockets: https://developer.mozilla.org/en-US/docs/Web/API/WebSocket
 * 
 * Opening a websocket:
 *      let ws = new WebSocket('ws://[IP]':'[port])
 *          Example: let ws = new WebSocket('ws://192.168.1.1:80')
 * 
 * Sending data:
 *      ws.send("dataHere")
 * 
 * Receiving data:
 *      ws.onmessage = function message(data) {
 *          //do stuff with the data
 *      }
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Global variables
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

import {registerSettings} from "./src/settings.js";
import { calibrationForm } from "./src/calibrationMenu.js";
export const moduleName = "MaterialPlane";

//Websocket variables
let ip = "192.168.1.189";       //Ip address of the websocket server
let port = "81";                //Port of the websocket server
var ws;                         //Websocket variable
let wsOpen = false;             //Bool for checking if websocket has ever been opened => changes the warning message if there's no connection
let wsInterval;                 //Interval timer to detect disconnections

//Token & movement related variables
let tokens = [];

let hideElements = false;
let enableModule = false;

let mirX = false;
let mirY = false;
let rot = false;
let sens = 0;
let coordsCurrent = [];
let dialog;
let calEn = false;
let offsetEn = false;
let compX = 0;
let compY = 0;

let tokenTemp;
let movementMethod = 0;

let lowBattery = false;

class IRtoken {
    constructor() {
        this.controllingToken = false;  //Bool to store if a token is currently being controlled   
        this.controlledToken = false;   //Stores the currently controlled token
        this.storedPosition;            //Stores the startposition of a token when it starts moving
        this.currentPosition;           //Stores the current position of the token
    }

    /**
     * New IR coordinates were received. Coordinates will be scaled. If a token is near the scaled coordinate
     * @param {*} coords 
     */
    async update(coords){

        //Scale the coordinates so they correspond with the in-game coordinate system
        let scaledCoords = this.scaleIRinput(coords);   

        //Find the nearest token to the scaled coordinates
        let token = this.findToken( scaledCoords );
        //console.log("Token: ",token.name);
        
        //If no token was close enough, but a token is currently being controlled, move the token (assume physical movement was too fast for animation)
        if (this.controllingToken == true && (token == false || (token != false && token.id == this.controlledToken.id) ) ) {
            this.moveToken(this.controlledToken,scaledCoords);
        }
        //Else, if a token was close enough, and no token was selected previously, take control of this token and move it
        else if (token != false && this.controllingToken == false) {
            //If the user can control the token, or if the GM allows control over non-owned tokens
            if (token.can(game.user,"control") || game.settings.get(moduleName,'EnNonOwned')){
                if (token.can(game.user,"control"))  token.control();
                this.controlledToken = token;
                this.controllingToken = true;
                this.storedPosition = scaledCoords;
                
                this.moveToken(token,scaledCoords);
            }
        }
        else if (token == false){
            //if (this.controlledToken != false)
            //this.controlledToken.release();
            let tokens = canvas.tokens.children[0].children;
            for (let i=0; i<tokens.length; i++)
                if (tokens[i]._controlled == true)
                    tokens[i].release();
        }
            
        //Else if a token was close enough, and the token was previously selected, move the token
        //else if (token != false && token.id == this.controlledToken.id) 
        //    this.moveToken(token,scaledCoords);
        
    }
    
    /**
     * Move the token to the new coordinates
     * @param {*} token 
     * @param {*} coords 
     */
    moveToken(token,coords) {
        //Compensate for the difference between the center of the token and the top-left of the token, and compensate for token size
        coords.x -= token.hitArea.width/2 +(token.data.width - 1)*canvas.scene.data.grid/2;
        coords.y -= token.hitArea.height/2 -(token.data.height - 1)*canvas.scene.data.grid/2;

        if (token.can(game.user,"control") != true) movementMethod = 0;

        //Default foundry movement method: update movement after dropping token
        if (movementMethod == 0) {
            let gridCoords = canvas.grid.getCenter(coords.x-canvas.scene.data.grid/2,coords.y-canvas.scene.data.grid/2);
            let newCoords = {
                x: (gridCoords[0]+canvas.scene.data.grid/2),
                y: (gridCoords[1]+canvas.scene.data.grid/2)
            }
            let newCoords2 = {
                x: (newCoords.x+canvas.scene.data.grid/2),
                y: (newCoords.y+canvas.scene.data.grid/2)
            }
            if (token.can(game.user,"control") && token.checkCollision(newCoords2,true) && game.user.isGM == false) return;
            this.currentPosition = coords;
            token.data.x = coords.x;
            token.data.y = coords.y;
            token.refresh();
            if (game.settings.get("core", "tokenDragPreview") && token.can(game.user,"control"))
                token.updateSource({noUpdateFog: false});
        }
        //Step-by-Step movement: when dragging the token, the token is moved every gridspace
        else if (movementMethod == 1) {
        
            //Get the coordinates of the center of the grid closest to the coords
            let gridCoords = canvas.grid.getCenter(coords.x-canvas.scene.data.grid/2,coords.y-canvas.scene.data.grid/2)

            let newCoords = {
                x: (gridCoords[0]+canvas.scene.data.grid/2),
                y: (gridCoords[1]+canvas.scene.data.grid/2)
            }
            let newCoords2 = {
                x: (newCoords.x+canvas.scene.data.grid/2),
                y: (newCoords.y+canvas.scene.data.grid/2)
            }
            
            if (this.storedPosition != newCoords && (token.checkCollision(newCoords2,true) == false || game.user.isGM)){
                token.update(newCoords);
                this.storedPosition = newCoords;
                this.currentPosition = newCoords;
            }
        }
        movementMethod = game.settings.get(moduleName,'movementMethod');
    }

     /**
     * Calculate the difference between the old coordinates of the token and the last measured coordinates, and move the token there
     */
    async dropIRtoken(){

        //If no token is controlled, return
        if (this.controllingToken == false) return;
        this.controllingToken = false;

        //Release token, if setting is enabled
        if (game.settings.get(moduleName,'deselect')) this.controlledToken.release();
        
        //Get the coordinates of the center of the grid closest to the coords
        let gridCoords = canvas.grid.getCenter(this.currentPosition.x-canvas.scene.data.grid/2,this.currentPosition.y-canvas.scene.data.grid/2)

        let newCoords = {
            x: (gridCoords[0]+canvas.scene.data.grid/2),
            y: (gridCoords[1]+canvas.scene.data.grid/2)
        }
        let newCoordsCollision = {
            x: (newCoords.x+canvas.scene.data.grid/2),
            y: (newCoords.y+canvas.scene.data.grid/2)
        }
        if (this.controlledToken.can(game.user,"control")) await this.controlledToken.update(this.storedPosition);
        if (this.storedPosition != newCoords ){
            if ((this.controlledToken.can(game.user,"control") && this.controlledToken.checkCollision(newCoordsCollision) == false) || game.user.isGM) {
                //canvas.dimensions.size *= 50;
                this.controlledToken.update(newCoords);
                //canvas.dimensions.size /= 50;
            }
            else if (this.controlledToken.can(game.user,"control") != true)
                this.requestMovement(this.controlledToken,newCoords)
            this.storedPosition = newCoords;
        }
        else {
            let gridCoords = canvas.grid.getCenter(this.storedPosition.x-canvas.scene.data.grid/2,this.storedPosition.y-canvas.scene.data.grid/2)
            let newCoords = {
                x: (gridCoords[0]+canvas.scene.data.grid/2),
                y: (gridCoords[1]+canvas.scene.data.grid/2)
            }
            if (this.controlledToken.can(game.user,"control")) {
                this.controlledToken.update(newCoords);
            }
        }
    }

    requestMovement(token,coords){
        let payload = {
            "msgType": "moveToken",
            "senderId": game.user.id, 
            "receiverId": game.data.users.find(users => users.role == 4)._id, 
            "tokenId": token.id,
            "newCoords": coords
        };
        game.socket.emit(`module.MaterialPlane`, payload);
    }

    /**
     * Scales the coordinates received from the IR sensor so they correspond with the in-game coordinate system
     * 
     * @param {*} coords Measured coordinates
     * @param {*} cornerComp Compensates for the difference between measured coordinates and token coordinates
     * @return {*} Scaled coordinates
     */
    scaleIRinput(coords,cornerComp=true){

        //If the coordinates are invalid, return
        if (coords.x < 0 || coords.x > 1022 || coords.y < 0 || coords.y > 1022) return;

        //Calculate the amount of pixels that are visible on the screen
        let horVisible = screen.width/canvas.scene._viewPosition.scale;
        let vertVisible = screen.height/canvas.scene._viewPosition.scale;

        //Calculate the scaled coordinates
        let posX = (coords.x/1023)*horVisible+canvas.scene._viewPosition.x-horVisible/2;
        let posY = (coords.y/1023)*vertVisible+canvas.scene._viewPosition.y-vertVisible/2;

        //Compensate for an offset due to the difference between the measured coordinate and the token coordinate
        if (cornerComp) {
         //   let edgeOffset = canvas.scene.data.grid/(2*canvas.scene._viewPosition.scale);
          //  posX -= edgeOffset;
          //  posY -= edgeOffset;
        }

        //Return the value
        return {"x":posX,"y":posY};
    }

    /**
     * Find the token closest to the coordinates
     * 
     * @param {*} position Coordinates
     * @return {*} Token closest to the coordinates
     */
    findToken(coords){
        
        //Get the gridsize in on-screen pixels
        let gridsize = canvas.scene.data.grid*canvas.scene._viewPosition.scale;

        //For all tokens on the canvas: get the distance between the token and the coordinate. If this is smaller than half the gridsize in both axes, 'token' is returned
        for (let token of canvas.tokens.children[0].children){
            let coordsCenter = token.getCenter(token.x,token.y);      
            if (Math.abs(coordsCenter.x - coords.x) < token.hitArea.width/2 && Math.abs(coordsCenter.y - coords.y) < token.hitArea.height/2)
                return token;  
        }
                   
        return false;
    } 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Functions
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

let panZoomNow = false;
let startCoords;
let startDist;
let startScale;

function panZoom(coords) {/*
    let a = coords.x1-coords.x0;
    let b = coords.y1-coords.y0;
    let x =coords.x0;
    let y = coords.y0;
    //If no earlier pan/zoom
    if (panZoomNow == false) {
        panZoomNow = true;

        startCoords = tokens[0].scaleIRinput({"x":x,"y":y},false);
        console.log("startCoords: ",startCoords);
        startDist = Math.sqrt(a*a+b*b);
        startScale = canvas.scene._viewPosition.scale;
    }
    else {
        let newDistance = Math.sqrt(a*a+b*b);
        let newScale = startScale * newDistance/startDist;
        
        let newCoords = tokens[0].scaleIRinput({"x":x,"y":y},false);
        let shiftX = -(newCoords.x-startCoords.x)+startCoords.x;
       // let shiftY = -(newCoords.y-startCoords.y)+startCoords.y;
       console.log("startCoords: ",startCoords);
       console.log("newCoords: ",newCoords);
        console.log("shiftX: "+shiftX);

        //canvas.pan({x:shiftX});
    }

*/

}

let calDialog;
/**
 * Analyzes the message received from the IR tracker.
 * If coordinates are received, scale the coordinates to the in-game coordinate system, find the token closest to those coordinates, and either take control of a new token or update the position of the image of that token
 * If no coordinates are received, move token to last recieved position
 * 
 * @param {*} msg Message received from the IR tracker
 */
async function analyzeWSmessage(msg,passthrough = false){
    let data = JSON.parse(msg);
 //   console.log(data);

    //Low battery warning: send notification every 5 minutes
    if (data.LB && lowBattery == false){
        lowBattery = true;
        ui.notifications.warn("Material Plane: "+game.i18n.localize("MaterialPlane.Notifications.Battery"));
        setTimeout(function(){ 
            lowBattery = false;
        }, 300000);
    }

    //Yes IR => update token
    if (data.V==1 && game.settings.get(moduleName,'menuOpen') == false && enableModule){
        tokens[0].update({"x":data.X0,"y":data.Y0});
    } 
    //Multiple points => pan & zoom
    else if (data.V==2 && game.settings.get(moduleName,'menuOpen') == false && enableModule){
        panZoom({"x0":data.X0,"y0":data.Y0,"x1":data.X1,"y1":data.Y1});


    }
    //No IR => drop token
    else if (data.V == 0 && game.settings.get(moduleName,'menuOpen') == false && enableModule){
        for (let i =0; i<4; i++) 
            if (tokens[i].controllingToken) 
                tokens[i].dropIRtoken(); 
        
    }

    //GM's calibration screen
    else if (game.user.isGM && game.settings.get(moduleName,'menuOpen')) {
        let change = false;
        for (let i=0; i<4; i++){
            let x = 0;
            let y = 0;
            let intensity = 0;
            if (data.V > i) {
                if (i == 0) {x = data.X0; y = data.Y0; intensity = data.I0;}
                else if (i == 1) {x = data.X1; y = data.Y1; intensity = data.I1;}
                else if (i == 2) {x = data.X2; y = data.Y2; intensity = data.I2;}
                else if (i == 3) {x = data.X3; y = data.Y3; intensity = data.I3;}
                dialog.newCoordinates(i,x,y,intensity);
            }
            else
            dialog.newCoordinates(i,0,0,0);
        }
        if (data.V > 0)change = true;
        let mirX_temp = (data.MX == 1)? true: false;
        let mirY_temp = (data.MY == 1)? true: false;
        let rot_temp = (data.R == 1)? true: false;
        let sens_temp = data.S + 1;
        let calEn_temp = (data.H == 1)? true: false;
        let offsetEn_temp = (data.O == 1)? true: false;
        let compX_temp = data.CX;
        let compY_temp = data.CY;

        if (mirX_temp != mirX) change = true;
        else if (mirY_temp != mirY) change = true;
        else if (rot_temp != rot) change = true;
        else if (sens_temp != sens) change = true;
        else if (calEn_temp != calEn) change = true;
        else if (offsetEn_temp != offsetEn) change = true;
        else if (compX_temp != compX) change = true;
        else if (compY_temp != compY) change = true;
        if (change){
            mirX = mirX_temp;
            mirY = mirY_temp;
            rot = rot_temp;
            sens = sens_temp;
            calEn = calEn_temp;
            offsetEn = offsetEn_temp;
            compX = compX_temp;
            compY = compY_temp;
            dialog.updateSett(mirX,mirY,rot,sens,calEn, offsetEn,compX,compY);
            dialog.render(true);
        }
    }
//console.log("menuOpen: "+game.settings.get(moduleName,'menuOpen'));
    if (data.V == 0) panZoomNow = false;

    //Calibration procedure
    if (data.V == -1 && enableModule) {           
        if (data.D != undefined){
            if (calDialog != undefined) calDialog.close();
            let calPoints = data.D;
            let content = `
                ${game.i18n.localize("MaterialPlane.CalDialog.Singlepoint1")}<br><br>
                ${game.i18n.localize("MaterialPlane.CalDialog.Singlepoint2")}<br><br>`;
            if (data.M == "MULTI") {
                content = `
                    ${game.i18n.localize("MaterialPlane.CalDialog.Multipoint1")}<br><br>
                    ${game.i18n.localize("MaterialPlane.CalDialog.Multipoint2")}<br><br>`;
            }
            if (data.M == "OFFSET") {
                content = `
                    ${game.i18n.localize("MaterialPlane.CalDialog.Offset1")}<br><br>
                    ${game.i18n.localize("MaterialPlane.CalDialog.Offset2")}<br><br>`;
            }
            if (calPoints >= 0 && calPoints < 4)
                content += calPoints + `/4 ${game.i18n.localize("MaterialPlane.CalDialog.PointsCalibrated")}<br>`;
            else if (calPoints == 4){
                content = `
                    ${game.i18n.localize("MaterialPlane.CalDialog.CalComplete")}<br><br>
                    ${game.i18n.localize("MaterialPlane.CalDialog.CalClose")}<br><br>`;
                setTimeout(function(){ calDialog.close(); }, 5000);
            }
            else if (calPoints == -1){
                content = `
                    ${game.i18n.localize("MaterialPlane.CalDialog.CalCancel")}<br><br>
                    ${game.i18n.localize("MaterialPlane.CalDialog.CalClose")}<br><br>`;
                setTimeout(function(){ calDialog.close(); }, 5000);
            }
            calDialog = new Dialog({
                title: "Material Plane: "+game.i18n.localize("MaterialPlane.CalDialog.Title"),
                content,
                buttons: {
                
                },
                default: "cancel"
            }).render(true);
        }

    }
    
};

/**
 * Start a new websocket
 * Start a 10s interval, if no connection is made, run resetWS()
 * If connection is made, set interval to 1.5s to check for disconnects
 * If message is received, reset the interval, and send the message to analyzeWSmessage()
 */
function startWebsocket() {
    ip = game.settings.get(moduleName,'IP');
    ws = new WebSocket('ws://'+ip+':'+port);

    ws.onmessage = function(msg){
        analyzeWSmessage(msg.data);
        clearInterval(wsInterval);
        wsInterval = setInterval(resetWS, 5000);
    }

    ws.onopen = function() {
        ui.notifications.info("Material Plane: "+game.i18n.localize("MaterialPlane.Notifications.Connected")+ip+':'+port);
        wsOpen = true;
        clearInterval(wsInterval);
        wsInterval = setInterval(resetWS, 5000);
    }
  
    clearInterval(wsInterval);
    wsInterval = setInterval(resetWS, 10000);
}

/**
 * Try to reset the websocket if a connection is lost
 */
function resetWS(){
    if (wsOpen) ui.notifications.warn("Material Plane: "+game.i18n.localize("MaterialPlane.Notifications.Disconnected"));
    else ui.notifications.warn("Material Plane: "+game.i18n.localize("MaterialPlane.Notifications.ConnectFail"));
    startWebsocket();
}


export function sendWS(txt){
    ws.send(txt);
}

export function calSettClosed(){
    game.settings.set(moduleName,'menuOpen',false);
}

/**
 * Check keys for 'Ctrl' press, to show or hide elements
 */

function checkKeys() {
    let fired = false;
    window.addEventListener("keydown", async (e) => { 
      if (fired){
        fired = false;
        if (hideElements){
            $('#logo').hide();
            $('#sidebar').hide();
            $('#navigation').hide();
            $('#controls').hide();
            $('#players').hide();
            $('#hotbar').hide();
        }
      }
      else if (e.key == "Control") {
        fired = true;
        if (hideElements){
            $('#logo').show();
            $('#sidebar').show();
            $('#navigation').show();
            $('#controls').show();
            $('#players').show();
            $('#hotbar').show();
        }
        
      }
    });
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hooks
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Ready hook
 * Attempt to open the websocket
 */
Hooks.on('ready', ()=>{
    enableModule = (game.user.name == game.settings.get(moduleName,'TargetName') && game.settings.get(moduleName,'Enable')) ? true : false;
    hideElements = game.settings.get(moduleName,'HideElements') && game.user.isGM == false;
    if (game.settings.get(moduleName,'Enable') && window.location.protocol == "https:"){
        ui.notifications.warn("Material Plane: "+game.i18n.localize("MaterialPlane.Notifications.SSL"));
        enableModule = false;
        return;
    }
    if (enableModule || game.user.isGM){
        startWebsocket();

        if (hideElements){
            $('#logo').hide();
            $('#sidebar').hide();
            $('#navigation').hide();
            $('#controls').hide();
            $('#players').hide();
            $('#hotbar').hide();
            checkKeys();
        }

    }

    game.socket.on(`module.MaterialPlane`, (payload) =>{
        //console.log(payload);
        
        if (game.user.id == payload.receiverId) {
            if (payload.msgType == "moveToken"){
                let token = canvas.tokens.children[0].children;
                for (let i=0; i<token.length; i++) {
                    if (token[i].id == payload.tokenId){
                        let tokenSel = token[i];
                        tokenSel.update({x: payload.newCoords.x, y: payload.newCoords.y});
                    }
                }
            }
        }    
    });
    movementMethod = game.settings.get(moduleName,'movementMethod');
    if (game.user.isGM) game.settings.set(moduleName,'menuOpen',false);
});
Hooks.on("renderSettings", (app, html) => {

/**
 * Create label and button in setup screen
 */
    const label = $(
        `<div id="MaterialPlane">
                <h4>Material Plane</h4>
            </div>
            `
    );
    const btn = $(
        `<button id="MaterialPlane_Calibration" data-action="MaterialPlane_Cal" title="Calibration Menu">
            <i></i> ${game.i18n.localize("MaterialPlane.CalSett.BtnName")}
        </button>`
    );

    const setupButton = html.find("button[data-action='setup']");
    setupButton.after(label);
    label.after(btn);

    btn.on("click", event => {
        game.settings.set(moduleName,'menuOpen',true);
        dialog = new calibrationForm();
        dialog.updateSett(mirX,mirY,rot,sens,calEn, offsetEn,compX,compY);
        dialog.render(true)
    });
});

Hooks.on('closecalibrationForm',() => {
    calSettClosed();
});


/**
 * Init hook
 * Initialize settings
 */
Hooks.once('init', function(){
    registerSettings(); //in ./src/settings.js

    

    for (let i=0; i<4; i++) tokens[i] = new IRtoken();
});

/**
 * Hide elements on various hooks
 */
Hooks.on('renderSceneNavigation', (app,html) => {
    if (hideElements) {
        html.hide();
    }
});

Hooks.on('renderSceneControls', (app, html) => {
    if (hideElements) {
        html.hide();
    }
});

Hooks.on('renderSidebarTab', (app, html) => {
    if (hideElements) {
        html.hide();
    }
});

Hooks.on('renderCombatTracker', (app, html) => {
    if (hideElements) {
        html.hide();
    }
});

Hooks.on('renderPlayerList', (app, html) => {
    if (hideElements) {
        html.hide();
    }
});