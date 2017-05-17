Hello. I hope you are having a wonderful day. If it's not wonderful, hopefully using the Hardlight Plugin won't make it any worse =)


Quickstart
----------

Within the Hardlight Plugin folder, you'll find two folders. 

'Binaries' - contains essential DLLs necessary for running in editor and packaged game 
'HapticSuit' - the UE4.15 plugin containing haptic assets and blueprints

0. Close your game.
1. Copy the HapticSuit folder into your project's Plugins directory. If Plugins doesn't exist, create it.

Your project should look a bit like this:

YourProject /
	Build
	Config
	Content
	..etc.
	Plugins
		HapticSuit <-- the Hardlight Plugin

2. Copy and paste the Binaries folder into your project so that it merges with your project's Binaries folder. If your project doesn't have a Binaries folder, that's fine; now it does.

The Binaries folder in your project should now look like this:

Binaries /
	Win32
		..stuff
		NSLoader.dll <-- important, should be present
	Win64
		..stuff
		NSLoader.dll <-- important, should be present

3. Right click on your .uproject and select Generate Visual Studio project files. If it says you need to add C++ files to the project, add an empty class first.

Open up VS and build your project. You should be good to go, if the Unreal Gods are smiling upon us today. 


Verify that it's functional
---------------------------

1. Open up a blueprint, such as your level blueprint. Use the node 'Play Test Routine' (just type 'Play test' and it should pop up).
2. Listen for 5 clicks from the suit when the node triggers. 


Utilities
--------
To check if the suit is plugged in, use the BP node Is Connected To Suit.
To check if the service is running, use the BP node Is Connected To Service. 


Haptics Quickstart
------------------
Create BP node 'Create Pattern Handle', select any pattern asset you want as input to the node, then drag out BP node 'Play'. Play the game.
See Haptics Theory for what this means or how to view the assets.


Haptics Theory
-------------

Haptics come in three related flavors - Sequences, Patterns, and Experiences. 

In Unreal, these are the UObjects UHapticSequence, UHapticPattern, and UHapticExperience.

They are essentially levels in a tree, with each node having a time offset within it's level. 

You might have a few sequences grouped together in a pattern, which is then grouped with other patterns in an experience.

This allows you to reuse your assets over and over, referencing them when needed. 
										
										
	HapticExperience   											
	|	
	|_X_____________________________X________________________X_____________________
	  t0.0 HapticPattern			t 1.0 HapticPattern 	 t 1.8 Haptic Pattern
	  | 							|						 |
	  |_x______x_________x____		|x__________x_____x		 |______xxxxx________
		seq    seq 		 seq		 seq 		seq   seq			seq	 	   	
		t0.2   t0.5		 t0.7		 t0.0 		t0.5  t0.65         t0.2 dur:.25



Why not use the same node type for each level - say, call everything a HapticSequence? The node types have fundamental differences.
 
Sequences conceptually run on one zone of the suit - "tap tap click". 
Patterns bring together multiple sequences, allowing you to make effects that span the suit - "lightning bolt from shoulder to arm".
Experiences bring together multiple patterns, allowing you to mix and match patterns - "lightning storm followed by beating heart".

You can browse our sample content in Unreal's Content Browser. To do this:
1. Look for the little 'View Options <o>' menu in the bottom right of the browser, and check 'Show Plugin Content'. 
2. Make sure the icon (little arrow menu thingy, 'Show or hide the sources panel' on top left of browser) is clicked so you can view a folder heirarchy. 
3. Find 'HapticSuit Content', expand it, and check out the Core, DeathAndDying, and Misc packages. 

You can right click -> Edit the assets to see how they are built. Right click-> Reference Viewer is also very helpful to visualize the tree structure and jump between assets. Be sure to drag the Search Depth Limit out to 2 to see the full Experience -> Pattern -> Sequence chain. 


Manipulating Playback
---------------------

A haptic handle ('Create Experience Handle', 'Create Pattern Handle', 'Create Sequence Handle') is your manipulation tool. You can 'Play', 'Pause', and 'Stop' an effect using these handles. 

Additionally, you can control the state of the entire haptics pipeline by using the BP nodes 'Pause all haptics', 'Resume all haptics', and 'Clear all haptics'. Note that 'Clear all haptics' will invalidate any handles you have,
so you'd only want to use it when switching levels or quitting the game. 


Packaging a game
----------------
1. Drag the 'Binaries' folder (the one directly inside 'Hardlight Plugin' that came with the kit) into your packaged project folder. That is, if your game is called
MyCoolGame, drag it into WindowsNoEditor/MyCoolGame where it will merge with the binaries folder there. 


Asset Loading
-------------
The haptic assets refer to eachother using TAssetPtr<>. This means the assets are not loaded until they are needed. The Create X Handle BP nodes synchronously load the assets when called, so if you have complex experiences, the game may skip frames. You can mitigate this by loading the assets up front or loading them asynchronously. We do not do this in the plugin yet. 


Advanced Effects
----------------
If you want full flexibility, you can use the lower level APIs. 
Constructs: Timelines, Events, and PlaybackHandles. Add a bunch of Events to a Timeline and then create a PlaybackHandle. 

For example:

auto timeline = FHapticSuitModule::Get().CreateTimeline();
timeline->Add(FBasicHapticEvent(time, duration, strength, effect, area));
auto handle = timeline->Transmit();
handle->Play();

Using this basic API, you can built up all kinds of effect generators. 