import * as MODULE from "../MaterialPlane.js";


export class calibrationForm extends FormApplication {
    constructor(data, options) {
        super(data, options);
        this.data = data;

       this.mirrorX = false;
       this.mirrorY = true;
       this.rotation = false;
       this.sensitivity = 0;
       this.calibrationEn = false;

       this.X0 = 0;
       this.Y0 = 0;
       this.I0 = 0;
       this.X1 = 0;
       this.Y1 = 0;
       this.I1 = 0;
       this.X2 = 0;
       this.Y2 = 0;
       this.I2 = 0;
       this.X3 = 0;
       this.Y3 = 0;
       this.I3 = 0;
    }

    /**
     * Default Options for this FormApplication
     */
    static get defaultOptions() {
        return mergeObject(super.defaultOptions, {
            id: "MaterialPlane_CalMenu",
            title: "Calibration Menu",
            template: "./modules/MaterialPlane/templates/calibrationMenu.html",
            classes: ["sheet"],
            width: 500
        });
    }
    
    newCoordinates(point, x, y, intensity){
        if (point == 0) {this.X0 = x; this.Y0 = y; this.I0 = intensity;}
        else if (point == 1) {this.X1 = x; this.Y1 = y; this.I1 = intensity;}
        else if (point == 2) {this.X2 = x; this.Y2 = y; this.I2 = intensity;}
        else if (point == 3) {this.X3 = x; this.Y3 = y; this.I3 = intensity;}
        //this.render();
    }

    updateSett(Mx,My,R,S,calEn){
        this.mirrorX = Mx;
        this.mirrorY = My;
        this.rotation = R;
        this.sensitivity = S;
        this.calibrationEn = calEn;
        console.log("Mx: "+Mx+" My: "+My+" rot: "+R+" sensitivity: "+S);
    }

    _updateObjects(event, formData){
        MODULE.calSettClosed();
    }



    /**
     * Provide data to the template
     */
    getData() {
        return {
            x0: this.X0,
            y0: this.Y0,
            i0: this.I0,
            x1: this.X1,
            y1: this.Y1,
            i1: this.I1,
            x2: this.X2,
            y2: this.Y2,
            i2: this.I2,
            x3: this.X3,
            y3: this.Y3,
            i3: this.I3,
            mirrorX: this.mirrorX,
            mirrorY: this.mirrorY,
            rotation: this.rotation,
            sens: this.sensitivity,
            cal: this.calibrationEn
        }
    }

    /**
     * Update on form submit
     * @param {*} event 
     * @param {*} formData 
     */
    async _updateObject(event, formData) {
        MODULE.calSettClosed();
    }

    activateListeners(html) {
        super.activateListeners(html);

        const mirX = html.find("input[name='mirX']");
        const mirY = html.find("input[name='mirY']");
        const rot = html.find("input[name='rot']");
        const sens = html.find("input[name='sens']");
        const disableCalBtn = html.find("button[name='disableCalBtn']");
        const calBtn = html.find("button[name='calBtn']");

        mirX.on("change", event => {
            let msg = "MIR X ";
            msg += event.target.checked? "1" : "0";
            MODULE.sendWS(msg);
        });

        mirY.on("change", event => {
            let msg = "MIR Y ";
            msg += event.target.checked? "1" : "0";
            MODULE.sendWS(msg);
        });

        rot.on("change", event => {
            let msg = "ROT ";
            msg += event.target.checked? "1" : "0";
            MODULE.sendWS(msg);
        });

        sens.on("change", event => {
            let msg = "SENS ";
            msg += event.target.value;
            MODULE.sendWS(msg);
        });

        disableCalBtn.on("click", event => {
            MODULE.sendWS("CAL EN 0");
        });

        calBtn.on("click", event => {
            let msg = "CAL "
            msg += (html.find("select[name='calMethod']")[0].value == "SinglePoint")? "SINGLE" : "MULTI";
            console.log(html.find("select[name='calMethod']")[0].value);
            MODULE.sendWS(msg);
            console.log("calBtn");
        });
    }
}




