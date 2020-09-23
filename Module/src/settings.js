import * as MODULE from "../MaterialPlane.js";
import { calibrationForm } from "./calibrationMenu.js";

export const registerSettings = function() {
console.log(MODULE.moduleName);
    

/**
     * Enables the module (world)
     */
    game.settings.register(MODULE.moduleName,'Enable', {
        name: "Enable module",
        scope: "world",
        config: true,
        default: true,
        type: Boolean,
        onChange: x => window.location.reload()
    });

    /**
     * Sets the movement method
     */
    game.settings.register(MODULE.moduleName,'movementMethod', {
        name: "Movement Method",
        hint: "Sets the movement method. 'Default' is the default Foundry behavior (vision updates after move), 'Step-by-Step' moves the token onto every grid you drag along, updating the vision every step",
        scope: "world",
        config: true,
        type:Number,
        default:0,
        choices:["Default","Step-by-step"],
        onChange: x => window.location.reload()
    });

    /**
     * Release the token after dropping
     */
    game.settings.register(MODULE.moduleName,'deselect', {
        name: "Deselect token after drop",
        hint: "Deselect the token when it is no longer dragged (works great in combination with the 'Hot Seat' module",
        scope: "world",
        config: true,
        default: false,
        type: Boolean,
        onChange: x => window.location.reload()
    });

    /**
     * Sets if the target client is allowed to move non-owned tokens
     */
    game.settings.register(MODULE.moduleName,'EnNonOwned', {
        name: "Non-owned movement",
        hint: "Enable the movement of non-owned tokens",
        scope: "world",
        config: true,
        default: true,
        type: Boolean,
        onChange: x => window.location.reload()
    });

    /**
     * Sets the name of the target client (who has the TV connected)
     */
    game.settings.register(MODULE.moduleName,'TargetName', {
        name: "Target Name",
        hint: "Name of the player who has the TV connected",
        scope: "world",
        config: true,
        default: "Observer",
        type: String,
        onChange: x => window.location.reload()
    });

    /**
     * Hides all elements on the target client, if that client is not a GM
     */
    game.settings.register(MODULE.moduleName,'HideElements', {
        name: "Hide Display Elements",
        hint: "Hides all display elements for the target player (if not GM). Client can hold 'Ctrl' to show the elements",
        scope: "world",
        config: true,
        default: false,
        type: Boolean,
        onChange: x => window.location.reload()
    });

    /**
     * Sets the name of the target client (who has the TV connected)
     */
    game.settings.register(MODULE.moduleName,'IP', {
        name: "Sensor Module IP",
        hint: "Fill in the IP address of the sensor module",
        scope: "world",
        config: true,
        default: "192.168.1.189",
        type: String,
        onChange: x => window.location.reload()
    });


    game.settings.registerMenu(MODULE.moduleName, 'calibrationMenu',{
        name: "Calibration Menu",
        label: "Calibration Menu",
        icon: "fas fa-cog",
        type: calibrationForm,
        restricted: true
    })




    //invisible settings
    game.settings.register(MODULE.moduleName,'menuOpen', {
        name: "Menu Open",
        hint: "Menu open on GM side",
        scope: "world",
        config: false,
        default: false,
        type: Boolean
    });


}