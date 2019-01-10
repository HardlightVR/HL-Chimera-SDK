# HL Chimera SDK

Distribution for the Hardlight Software Development Kit, windows service, and libraries. A download and install of this repository is all that is required to run a Hardlight suit given a compatible game.

## Instructions:

To install the Hardlight Runtime:

1. Close any games using the Hardlight SDK, and quit any existing Runtimes
2. Open `Runtime Installer` folder
3. Double click `HardlightRuntimeInstaller[version].exe` which will install the runtime and required dependencies.
4. If you are upgrading from a previous version, or uninstalling, note that you may have to quit HardlightControl manually if the installer is
unable to terminate it.
5. Open HardlightControl.exe, located at (Windows key -> "Recently Added") or in the install directory. A small icon will appear in your task tray. Right click the icon to:
    - Enable the runtime (may take up to 3 seconds for icon to turn green, meaning the runtime is enabled)
    - Disable the runtime (may take up to 3 seconds for icon to turn white, meaning the runtime is disabled)
    - Enable or disable analog audio mode
    - Test haptics on a particular device
    - Enable or disable tracking on a particular device
    - Check version of the Runtime
    - Fetch updates for the Runtime

### To uninstall:

1. Add/Remove programs --> Hardlight Runtime -> Uninstall

### To upgrade:

1. Right click on HardlightControl -> Updates -> Check now

**Note: the runtime must be enabled for effects to play on the suit.**

See the [Wiki](https://github.com/NullSpaceVR/NullSpace-Chimera-SDK/wiki) for common issues, quickstart, and SDK usage.

## Please note:
Hardlight VR was a complex project involving many dependencies. We have decided to open the code in the hopes that others may make use of the tools and plugins we built over the last 5 years. However, some software may not have been built or tested in some time, and may require changes to be used with the latest VR software and technology. 

## Contributing and Contact
We welcome any and all interest in derivative projects made from this software, edits to the software, and updates to the plugins and drivers! If you are interested in contributing to the public Hardlight repositories, please create an issue, or email hardlightvr@gmail.com. 
