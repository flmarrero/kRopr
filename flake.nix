{
  description = "fx's nix-config";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";

    metaflakes = {
        url = "github:flmarrero/metaflakes";
        inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, flake-utils, ... }@inputs:
    let
      system = "x86_64-linux";

      pkgs =
        import inputs.nixpkgs
          {
            inherit system;
          };
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        inputsFrom = inputs.metaflakes.devShells.${system}.kernel.buildInputs;

        C_INCLUDE_PATH="${pkgs.linuxHeaders}/include";

        nativeBuildInputs = with pkgs; [
                linuxHeaders
                
        ];
      };

      packages.${system}.test-driver = import ./test/default.nix { inherit pkgs; };
    };
}
