//Copyright (c) 2011 Oscar (.teri) Triano <teritriano@gmail.com>

//This software is provided 'as-is', without any express or implied
//warranty. In no event will the authors be held liable for any damages
//arising from the use of this software.

//Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
//freely, subject to the following restrictions:

   //1. The origin of this software must not be misrepresented; you must not
   //claim that you wrote the original software. If you use this software
   //in a product, an acknowledgment in the product documentation would be
   //appreciated but is not required.

   //2. Altered source versions must be plainly marked as such, and must not be
   //misrepresented as being the original software.

   //3. This notice may not be removed or altered from any source
   //distribution.

#include <iostream>
#include <sfmlphysfs.hpp>
#include <image.hpp>

void bange::image::RegisterVM(lua_State *vm){
    luaL_Reg functions[] = {
    {"LoadImage", bange::LoadImage},
    {"LoadImageFromPackage", bange::LoadImageFromPackage},
    {NULL, NULL}};
    luaL_register(vm, "bange", functions);
    lua_pop(vm, 1);
}

int bange::LoadImage(lua_State *vm){
    //string -> bange::image
    if (!lua_isstring(vm, 1) || (lua_isstring(vm, 1) && lua_isnumber(vm, 1)) ){
        std::cout << "bange.LoadImage: First argument must be a string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if(lua_objlen(vm, 1) == 0){
        std::cout << "bange.LoadImage: The string is void." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    const char *filename = lua_tostring(vm, 1);
    bange::image *image = new bange::image;
    image->LoadFromFile(std::string(filename));
	bange::BuildProxy(vm, image);
    return 1;
}

int bange::LoadImageFromPackage(lua_State *vm){
    //string -> bange::image
    if (!lua_isstring(vm, 1) || (lua_isstring(vm, 1) && lua_isnumber(vm, 1)) ){
        std::cout << "bange.LoadImageFromPackage() -> First argument must be a string." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    if(lua_objlen(vm, 1) == 0){
        std::cout << "bange.LoadImageFromPackage() -> The string is void." << std::endl;
        lua_pushnil(vm);
        return 1;
    }
    const char *filename = lua_tostring(vm, 1);
    sf::physfs *streamimage = new sf::physfs(filename);
	bange::image *image = new bange::image;
	image->LoadFromStream(*streamimage);
	bange::BuildProxy(vm, image);
    delete streamimage;
    return 1;
}
