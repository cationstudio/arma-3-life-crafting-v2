/*
    File: stations.cpp
    Author: Julian Bauer (julian.bauer@cationstudio.com)

    Description:
    Station configuration for crafting system.
*/
class craftingItems {
    spawnmarker = ""; // name of marker where vehicle should spawn. Marker must be available on map
    categories[] = {"item","weapon"}; // defined in categories.cpp: enter classnames
};

class craftingClothes {
    spawnmarker = "";
    categories[] = {"uniform","backpack","vest"};
};

class craftingVehicles {
    spawnmarker = "craftingVehiclesMarker";
    categories[] = {"landvehicle","airvehicle","watervehicle"};
};