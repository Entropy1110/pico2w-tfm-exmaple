❯ cmake -S </absolute/path/of/trusted-firmware-m> -B ./spe -DTFM_PLATFORM=rpi/rp2350 -DTFM_PROFILE=profile_small -DPICO_SDK_PATH=</absolute/path/of/pico-sdk> -DITS_ENCRYPTION=OFF
❯ cmake --build ./spe -- -j6 install
