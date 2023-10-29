TODO List:

1. Done - Create Log class to encapsulate spdlog calls.
2. In Progress - Add error logging where necessary.
3. In Progress - Add debug logging everywhere.
4. Possibly create separate engine and client loggers.
5. Add config file to set things like default font, log level, etc.
6. Done - Create TextureAtlas class.
7. Done - Add AnimatedSprite class.
8. Make release and debug builds actually do release and debug builds.
9. Consider removing non-sparky types and includes from public headers. This should remove the need
to include any non-sparky headers in the install package.
    - DONE - Font.h - freetype-gl.h
    - DONE - ImageUtils.h - freeimage.h
    - CANCELED - Need templates at header level - LogUtils.h - spdlog.h
10. Write documentation!

