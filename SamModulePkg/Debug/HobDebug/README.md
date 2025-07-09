
# How to use `HobDebug`

## 1. Configuration

- Add `HobDxe.inf` and `HobPei.inf` into OvmfPkgX64.dsc, like below:

```dsc

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform.
#
################################################################################
[Components]
# Add this
...
  #
  # PEI Phase modules
  #
  SamModulePkg/Debug/HobDebug/Pei/HobPei.inf
...
  #
  # DXE Phase modules
  #
  SamModulePkg/Debug/HobDebug/Dxe/HobDxe.inf
...
```

- Add `HobDxe.inf` and `HobPei.inf` into OvmfPkgX64.fdf, like below:

```fdf
...
#
#  PEI Phase modules
#
INF  SamModulePkg/Debug/HobDebug/Pei/HobPei.inf
...
#
# DXE Phase modules
#
INF  SamModulePkg/Debug/HobDebug/Dxe/HobDxe.inf
...
```

- Build OVMF:

```shell
build -p OvmfPkg/OvmfPkgX64.dsc -t GCC5 -a X64 -b DEBUG
build -p OvmfPkg/OvmfPkgX64.dsc -t VS2022 -a X64 -b DEBUG
```

- Run OVMF.fd

```shell
qemu-system-x86_64 \
-drive if=pflash,format=raw,file=OVMF.fd,id=BIOS-OVMF \
-drive file=fat:rw:hda-contents,format=raw,if=ide,index=0 \
-debugcon file:debug.log \
-global isa-debugcon.iobase=0x402 \
-s
```
