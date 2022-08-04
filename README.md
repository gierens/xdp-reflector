# xdp-reflector
An XDP program to reflect ethernet frames.

## Performance
With [MoonGen](https://github.com/emmericp/MoonGen/) I achieved about 1.6 Mpps on an Intel 82599-based NIC.
I'm not entirely sure yet if and how one can achieve the 14 Mpps that would
max out the 10 Gbps throughput of the card.

## Dependencies
Initialize the [libbpf](https://github.com/libbpf/libbpf)
submodule with:
```bash
git submodule update --init
```
Then install the remaining dependencies with:
```bash
sudo apt install -y clang llvm libelf-dev libpcap-dev gcc-multilib build-essential linux-headers-$(uname -r)
```
For installation instructions for non-Debian systems see
[XDP tutorial's setup instructions](https://github.com/xdp-project/xdp-tutorial/blob/master/setup_dependencies.org)

## Building
Just hit `make`:
```bash
make
```

## Deploying
Due to the simplicity of this XDP program, it does not come with an extra
loader. You can simply use the `ip` tool for this.

To attach the reflector to a device use:
```bash
sudo ip link set <DEV> xdpgeneric obj reflector.o sec xdp
```
And to remove it again use:
```bash
sudo ip link set <DEV> xdpgeneric off
```

## Remarks
This is quite a tiny and almost trivial project. I wrote it because I needed
a fast reflector to take [MoonGen](https://github.com/emmericp/MoonGen/)
measurements on non-PCI devices in [QEMU](https://github.com/qemu/qemu/)
guests. Apart from such usecases it can serve as a minimal sample project
for XDP programs.

This project is similarly structured as the
[XDP tutorial](https://github.com/xdp-project/xdp-tutorial),
which is a great resource for learning XDP prorgamming.

## License
This project is distributed under [MIT](LICENSE) license.
