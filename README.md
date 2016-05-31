# virtualrealm

A generic streaming server for multiplayer gameplay on mobile phones. Clients connect to a realm instance, then can navigate the surrounding space or deploy their own executable subrealms, which neighboring clients can wander into with their own avatar and join.

Subrealms are packages written in JavaScript which may or may not include external models, textures, or other static assets. An API for the instance of the subrealm on the network, as well as an assortment of models, textures, map tiles, and assorted assets, are all exposed to the scriptable JavaScript environment, which acts as a generic third-person game framework in a familiar language for developers.

`virtualrealm` is inspired by old-school Warcraft III, where custom maps (most notably DotA) could be deployed on a peer-to-peer network and played in small groups. In `virtualrealm`, subrealms are deployed on a closed, SSL encrypted network, so they can be hosted by anyone (normally NAT would be an issue on mobile networks). A subrealm is fully programmable, and may allow you to play with your global character, a character saved to the subrealm, or a temporary character which exists while you are connected to the subrealm. Regardless, when the client connects, it renders a 3rd person visual experience with similar controls across any subrealm, for Android or iOS.

Tools for compiling subrealm packages will exist that will allow ordinary people, even individuals without any prior programming experience, to create subrealms to enjoy with their friends in one sitting.

Subrealms can naturally contain triggers to display sponsored content to clients. Ad-supported subrealms are expected to form a major constituent of the subrealm ecosystem.

In many ways a `virtualrealm` client is like a web browser, with subrealms forming the ecosystem. The major difference is that your avatar on the server exists at a spatial position and is represented by some kind of graphic which you can navigate around the surrounding space. The connection with the server is streaming and connects you with all other clients on the subrealm (naturally, parallel clients have no access to protected resources).

## Build

Set `BOOST_ROOT` in `CMakeLists.txt` to wherever you have Boost installed. Make a build directory then run `cmake` to generate Makefile, then run `make`.

```
mkdir build
cd build
cmake ..
make
```


## Test
Tests are built with the application. To run the tests, perform the same steps as above then run `make test`.

```
mkdir build
cd build
cmake ..
make
make test
```
