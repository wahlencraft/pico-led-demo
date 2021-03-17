add_executable(demo
        demo.c
        )

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(demo pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(demo 1)
pico_enable_stdio_uart(demo 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(demo)

# add url via pico_set_program_url
example_auto_set_url(demo)
