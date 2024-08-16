Mini movement is determined by the selected [touch mode](./Foundry/foundryConfig.md#touch-modes).

* <b>Direct:</b> Touch and drag a token to move it. 
* <b>Tap Timeout:</b> Touch a token for a short amount of time (configured by the ['Tap Timeout'](./Foundry/foundryConfig.md#touch) setting), after which a token can be moved. For infrared touch frames it is required to raise the mini before movement.
* <b>Raise Mini:</b> To move a mini, you must first raise the mini from the screen, then after lowering it again on the screen, you can move it around.
This raise mini procedure is implemented to counter some of the issues related to touch frames: In certain situations, movement of a mini can influence the detected location of another mini. Since that other mini is probably not activated when this issue occurs, it should no longer be influenced by the movement of the first mini.

The token that is nearest to the touch will be activated (within approximately 1 grid space). So if there are 2 tokens next to each other, you have to make sure that you touch the correct token.

Once a token has been activated, it will be selected and follow the touch. The exact movement and vision behavior is determined by the ['Movement Method'](./Foundry/foundryConfig.md#control). The token will be dropped once no movement is detected for a certain period of time (determined by ['Token Drop Timeout'](./Foundry/foundryConfig.md#touch)), so to ensure that a token isn't accidentally dropped, you might want to keep moving it.

If the token is at its desired location, you release the touch, and it will be dropped after some time (determined by ['Token Drop Timeout'](./Foundry/foundryConfig.md#touch)). If ['Deselect Token After Drop'](./Foundry/foundryConfig.md#control) is enabled the token will be deselected, which will cause Foundry to display the vision of all owned tokens, otherwise the token will stay selected until deselected through some other means.