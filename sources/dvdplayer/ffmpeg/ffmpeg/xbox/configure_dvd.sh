./configure --extra-cflags="-D_XBOX -DUSE_FASTMEMCPY -I$PWD -I$PWD/lib/dts" --extra-ldflags="" --extra-libs="-L$PWD/lib/dts" \
	--disable-decoders \
	--disable-encoders \
	--enable-codec=mpegvideo_decoder \
	--enable-codec=mpeg1video_decoder \
	--enable-codec=mpeg2video_decoder \
	--enable-codec=mp2_decoder \
	--enable-codec=mpegvideo_parser \
	--enable-codec=mpegaudio_parser \
	--enable-codec=ac3_parser \
	--enable-codec=dvdsub_parser \
	--enable-codec=pcm_s16le_decoder \
	--enable-codec=pcm_s16be_decoder \
	--enable-codec=pcm_s16be_decoder \
	--enable-codec=pcm_pcm_u16be_decoder \
	--enable-codec=pcm_pcm_s8_decoder \
	--enable-codec=pcm_pcm_u8_decoder \
	--enable-codec=pcm_pcm_alaw_decoder \
	--enable-codec=pcm_pcm_mulaw_decoder \
	--enable-shared \
	--cpu=x86 --enable-mmx --enable-gpl \
	--disable-altivec \
	--disable-audio-oss \
	--disable-audio-beos \
	--disable-v4l \
	--disable-bktr \
	--disable-dv1394 \
	--disable-network \
	--disable-zlib \
	--disable-vhook \
	--disable-debug \
	--disable-ffserver \
	--disable-pp --enable-memalign-hack --enable-mingw32 
