
<div>
    <a href="https://bitbucket.org/matanelabayof/robbery-in-the-depths/src/master/"><img src="https://bitbucket.org/matanelabayof/robbery-in-the-depths/raw/b3b840ce807fdb514270d3ba91cd6ba439b648d3/oop2_project/textures/diver.png" alt="Jazz² Resurrection" title="Robbery in the Depths"></a>
</div>

<div>
    Open-source <strong>Robbery in the Depths</strong>
</div>

<div>
  <sub>
    Developed by <a href="https://bitbucket.org/matanelabayof/">@MatanelAbayof</a>, <a href="https://bitbucket.org/nahumnoga1/">@NahumNoga</a>, <a href="https://bitbucket.org/Akiva+Goldstein/">@AkivaGoldshtein</a>
  </sub>
</div>
<hr/>


## Introduction
Robbery in the Depths is 2D game

This project uses [SFML library](https://www.sfml-dev.org/download/sfml/2.5.1/).


## Preview
<div>
    <img src="https://raw.githubusercontent.com/deathkiller/jazz2/master/Docs/Screen2.gif" alt="Preview">
</div>

<div><a href="https://www.youtube.com/playlist?list=PLfrN-pyVL7k6n2VJF197F0yVOZq4EPTsP">Watch gameplay videos</a></div>


## Running the application
### Windows / Linux / macOS
* Download **Desktop** release (alternatively, build the solution and copy `Content` directory to `‹Game›/Content/`)
* Run `‹Game›/Import.exe "Path to original JJ2"` (or drag and drop original *Jazz Jackrabbit 2* directory on `Import.exe`)
  * On Linux and macOS, you can run `mono Import.exe "Path to original JJ2"`
* Run `‹Game›/Jazz2.exe`
  * On Linux and macOS, you can run `mono Jazz2.exe`

`‹Game›` *is path to Jazz² Resurrection. You can run* `Import.exe` *without parameters to show additional options.*

### Android
* Download both **Desktop** and **Android** releases (alternatively, build the solution and copy `Content` directory to `‹Game›/Content/`)
* Run `‹Game›/Import.exe "Path to original JJ2"` (or drag and drop original *Jazz Jackrabbit 2* directory on `Import.exe`)
* Copy `‹Game›/Content/` directory to `‹Storage›/jazz2.android/Content/`
  * Alternatively, you can use `‹Storage›/Android/Data/jazz2.android/Content/` instead
  * Create empty file `.nomedia` in `‹Storage›/jazz2.android/` to hide files from *Android Gallery*
* Install `Jazz2.apk` on Android device
* Run the newly installed application

*Requires device with Android 5.0 (or newer) and OpenGL ES 3.0 support.* `‹Storage›` *could be internal (preferred) or external storage.
The application tries to autodetect correct paths.*

### WebAssembly
* Go to [Jazz² Resurrection](http://deat.tk/jazz2/wasm/) page to play **Shareware Demo** online
  * Alternatively, build the solution and copy `Content` directory from **Desktop** release to build target directory

*Requires Google Chrome 57 (or newer), Firefox 53 (or newer) or other browser supporting WebAssembly and WebGL.*


## Dependencies
### Windows
* .NET Framework 4.5.2 (or newer)
* [OpenAL Soft](https://github.com/opentk/opentk-dependencies) (included in release)
  * Copy `x86/openal32.dll` to `‹Game›/Extensions/OpenALSoft.x86.dll`
  * Copy `x64/openal32.dll` to `‹Game›/Extensions/OpenALSoft.x64.dll`
* [libopenmpt](https://lib.openmpt.org/libopenmpt/download/) (included in release)
  * Copy `libopenmpt.dll` (*x86*, and its dependencies) to `‹Game›` directory

### Linux
* [Mono 5.0 (or newer)](http://www.mono-project.com/download/#download-lin)
* OpenAL
  * Run `sudo apt install openal1` if it's missing
* [libopenmpt](https://lib.openmpt.org/libopenmpt/download/) (included in release)
  * Copy `libopenmpt.so` (*x86*, and its dependencies) to `‹Game›` directory

### macOS
* [Mono 5.0 (or newer)](http://www.mono-project.com/download/#download-mac)
* OpenAL should be already installed by OS
* [libopenmpt](https://lib.openmpt.org/libopenmpt/)
  * Copy `libopenmpt.dylib` (*x86*, and its dependencies) to `‹Game›` directory

### Android
* Xamarin
* [OpenAL Soft](https://github.com/kcat/openal-soft) (included for *armeabi-v7a* and *x86*)
* [libopenmpt](https://lib.openmpt.org/libopenmpt/download/) (included for *armeabi-v7a* and *x86*)

### WebAssembly
* .NET Framework 4.5.2 (or newer) / Mono 5.0 (or newer)
* `Mono.WebAssembly.Sdk` (included as NuGet)
* [WebGL.NET](https://github.com/WaveEngine/WebGL.NET) (included)

## Building the solution
### Windows
* Open the solution in [Microsoft Visual Studio 2019](https://www.visualstudio.com/) (or newer) and build it
* Copy `/Packages/AdamsLair.OpenTK.x.y.z/lib/OpenTK.dll.config` to `/Jazz2/Bin/Debug/OpenTK.dll.config`
* Copy dependencies to `/Jazz2/Bin/Debug/` or `/Jazz2/Bin/Release/`
* If you build Release configuration, you have to replace `Debug` with `Release` in paths above

### Linux
* Install [Mono 5.0 (or newer)](http://www.mono-project.com/download/#download-lin)
* Run `msbuild` in directory with the solution file (.sln):
* Copy `/Packages/AdamsLair.OpenTK.x.y.z/lib/OpenTK.dll.config` to `/Jazz2/Bin/Debug/OpenTK.dll.config`
* Obtain and copy `libopenmpt.so` to `/Jazz2/Bin/Debug/libopenmpt.so` to enable music playback
* Then you can rebuild the solution only with `msbuild` command
* Use `msbuild /p:Configuration=Release` to build Release configuration, you have to replace `Debug` with `Release` in paths above

### macOS
* Install [Mono 5.0 (or newer)](http://www.mono-project.com/download/#download-mac)
* Open the solution in [Microsoft Visual Studio for Mac](https://www.visualstudio.com/vs/visual-studio-mac/) and build it
* Copy `/Packages/AdamsLair.OpenTK.x.y.z/lib/OpenTK.dll.config` to `/Jazz2/Bin/Debug/OpenTK.dll.config`
* Obtain and copy `libopenmpt.dylib` to `/Jazz2/Bin/Debug/libopenmpt.dylib` to enable music playback
* If you build Release configuration, you have to replace `Debug` with `Release` in paths above

***.NET Core 3.0** build can be compiled in a similar way (use* `Jazz2.DotNetCore` *project). Compile errors about* `Jazz2.Android` *project can be ignored, if the Android build is not needed.*

### Android
* Install **Mobile development in .NET** for Microsoft Visual Studio 2019 (or newer)
* Open the solution and build `Jazz2.Android` project
* Dependencies are already included for common configurations

### WebAssembly
* Open the solution and build `Jazz2.Wasm` project
* Dependencies are already included for common configurations


## Extensions
### OpenGL ES 2.0 (Experimental)
Alternative OpenGL ES 2.0 backend can be built separately. It does not contain all features
that are available in default OpenGL 2.1 backend, but it should run faster on low-end configurations.
Don't use it if you have no reason to do so!

To use it, build `Extensions/Es20Backend` project. The library will be copied to
`/Jazz2/Bin/Debug/Extensions/Es20Backend.core.dll` automatically.
Then copy all files from `Content/_ES20` directory to `/Jazz2/Bin/Debug/Content` and replace them.

Also, you have to remove `/Jazz2/Bin/Debug/Extensions/GL21Backend.core.dll` file to disable default OpenGL 2.1 backend.


## License
This project is licensed under the terms of the [GNU General Public License v3.0](./LICENSE).