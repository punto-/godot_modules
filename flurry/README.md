Flurry
======

This is the Flurry module for Godot Engine (https://github.com/okamstudio/godot)

How to use
----------
Drop the "flurry" directory inside the "modules" directory on the Godot source. Recompile for your platform.

Add the SDKs
------------
Because we're not sure if we can distribute the Flurry library, it was removed from this repository, you need to download it and add it yourself.

- On Android: put the file "FlurryAgent.jar" file inside android/
- On iOS: put the Flurry header file ("Flurry.h") and the library ("libFlurry.a") inside ios/
- On Blackberry: put the contents of the Flurry SDK inside bps/. The directory contents should look like this:

```
bps/
bps/Flurry
bps/Flurry/x86
bps/Flurry/x86/libFlurry.a
bps/Flurry/armle-v7
bps/Flurry/armle-v7/libFlurry.a
bps/Flurry.h
bps/FlurryC.h
```

- Everywhere else: the file "flurry_dummy.cpp" will be compiled, to provide a dummy version of the API.

Configuring your game
---------------------

To enable the module on Android, add the path to the module to the "modules" property on the [android] section of your engine.cfg file. It should look like this:

	[android]
	modules="com/android/godot/GodotFlurry"

Note this is a comma separated list inside a string, you can have other modules there.

On iOS and Blackberry, the module is enabled by default.

To configure your API key, set the "api_key" property on the [flurry] section on your engine.cfg. Example:

	[flurry]
	api_key="0123456789abcdef"

Note that you can override the section for specific platforms, example:


	[flurry.Android]
	api_key="0123456789abcdef"

	[flurry.iOS]
	api_key="0123456789abcdf0"

	[flurry.QNX] # this is Blackberry
	api_key="0123456789abcdf1"

API Reference
-------------

The singleton "Flurry" will be available on gdscript.

The following methods are available, defined on the file flurry.h:

        void log_event(String p_name, Dictionary p_params);
        void log_timed_event(String p_name, Dictionary p_params);
        void end_timed_event(String p_name);

Example:

```
func game_start():
	Flurry.log_timed_event("user_session", {"name": user_name})

func user_scored():
	Flurry.log_event("user_scored", {})

func game_over():
	Flurry.end_timed_event("user_session")
```



