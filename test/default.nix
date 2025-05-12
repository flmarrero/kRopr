{ 
  pkgs
}:

let
  kernel = pkgs.linuxPackages.kernel;
  lib = pkgs.lib;
  stdenv = pkgs.stdenv;
in
stdenv.mkDerivation {
  pname = "kropr-test-driver";
  version = "0.0.0-dev";

  src = ./.;

  nativeBuildInputs = kernel.moduleBuildDependencies;
  hardeningDisable = [ "pic" "format" ];

  makeFlags = kernel.makeFlags ++ [
    "KERNELRELEASE=${kernel.modDirVersion}"
    "KERNELDIR=${kernel.dev}/lib/modules/${kernel.modDirVersion}/build"
  ];

  buildFlags = [ "modules" ];
}
