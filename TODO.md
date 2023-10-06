TODO List:

1. DONE - Create Log class to encapsulate spdlog calls.
2. Add error logging where necessary.
3. Add debug logging everywhere.
4. Possibly create separate engine and client loggers.
5. Add config file to set things like default font, log level, etc.
6. Create TextureAtlas class.
    - How to make Sprite reference TextureAtlas?
        - Since Sprite accepts texture coordinates, just obtain coordines
        from the TextureAtlas
    - TextureAtlas
        - Texture* m_texture
        - std::vector&lt;std::vector&lt;vec2&rt;&rt; m_uv
        - If all sprites are same width/height, can calculate tex coords based on that
        - If sprites have different width/height, will need some way to specify coords
        for each sprite (load from text file?)

