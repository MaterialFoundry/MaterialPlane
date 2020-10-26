import * as MODULE from "../MaterialPlane.js";
import { calibrationForm } from "./calibrationMenu.js";

export const registerSettings = function() {
    
/**
     * Enables the module (world)
     */
    game.settings.register(MODULE.moduleName,'Enable', {
        name: "MaterialPlane.Sett.En",
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
        name: "MaterialPlane.Sett.MovementMethod",
        hint: "MaterialPlane.Sett.MovementMethod_Hint",
        scope: "world",
        config: true,
        type:Number,
        default:0,
        choices:["MaterialPlane.Sett.MovementMethod_Default","MaterialPlane.Sett.MovementMethod_SbS"],
        onChange: x => window.location.reload()
    });

    /**
     * Release the token after dropping
     */
    game.settings.register(MODULE.moduleName,'deselect', {
        name: "MaterialPlane.Sett.Deselect",
        hint: "MaterialPlane.Sett.Deselect_Hint",
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
        name: "MaterialPlane.Sett.NonownedMovement",
        hint: "MaterialPlane.Sett.NonownedMovement_Hint",
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
        name: "MaterialPlane.Sett.TargetName",
        hint: "MaterialPlane.Sett.TargetName_Hint",
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
        name: "MaterialPlane.Sett.HideDisplay",
        hint: "MaterialPlane.Sett.HideDisplay_Hint",
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
        name: "MaterialPlane.Sett.SensorIP",
        hint: "MaterialPlane.Sett.SensorIP_Hint",
        scope: "world",
        config: true,
        default: "192.168.1.189",
        type: String,
        onChange: x => window.location.reload()
    });

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