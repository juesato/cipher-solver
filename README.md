cipher-solver
=============

Main files are decrypt.cpp and decrypt_no_spaces.cpp, which both come compiled. Decrypt works by looking at 2-letter pattern frequencies and then refining the key to match English words, the no spaces case surprisingly doesn't require any knowledge of English words and works with just 3-letter pattern frequencies on sufficiently long text (generally around 100 words).
