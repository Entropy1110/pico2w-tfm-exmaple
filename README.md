# Directions
## Setting up directories
❯ `git clone --recursive https://github.com/Entropy1110/pico2w-tfm.git`

❯ `cd pico2w-tfm/pico2w-tfm-exmaple && mkdir build && cd build`

## Building SPE
❯ `cmake -S </absolute/path/to/pico2w-trusted-firmware-m> -B ./spe -DTFM_PLATFORM=rpi/rp2350 -DPICO_BOARD=pico2_w -DTFM_PROFILE=profile_medium -DPICO_SDK_PATH=</absolute/path/to/pico-sdk> -DPLATFORM_DEFAULT_PROVISIONING=OFF`

❯ `cmake --build ./spe -- -j8 install`

## Building NSPE
❯ `cmake -S </path/to/pico2w-tfm/pico2w-tfm-exmaple> -B ./nspe -DTFM_PLATFORM=rpi/rp2350 -DPICO_SDK_PATH=</absolute/path/to/pico-sdk> -DCONFIG_SPE_PATH=</absolute/path/to/spe/api_ns> -DPICO_BOARD=pico2_w -DTFM_TOOLCHAIN_FILE=</absolute/path/to/spe/api_ns/cmake/toolchain_ns_GNUARM.cmake>`

❯ `cmake --build ./nspe -- -j8`

## Convert SPE/NSPE into a UF2 for Flashing
❯ `cd </path/to/pico2w-tfm>`

❯ `./pico_uf2.sh pico2w-tfm-exmaple build`