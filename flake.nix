{
    description = "pong";
  
    inputs = 
    { 
        nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
        flake-utils.url = "github:numtide/flake-utils";
    };

    outputs = { self, nixpkgs, flake-utils}:
        flake-utils.lib.eachDefaultSystem 
        ( 
            system: 
            let
                pkgs = nixpkgs.legacyPackages.${system};
            in
            {
            devShells.default = pkgs.mkShell 
            {
                name = "pong";
                buildInputs = with pkgs; 
                [
                    clang_16
                    fmt
                    cmake
                    ninja
                    ncurses
                ];
            };
        }
    );
}
