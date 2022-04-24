# arma-3-life-crafting-v2

This is a crafting script for ArmA 3 RPG Life.

## Installation

A working installation of ArmA Life RPG Framework is required for a successful installation. Modifying the ArmA Life RPG Framework could cause errors – feel free to connect to our discord if you have a problem.

### Step 1

Download the newest release and extract the archive. Copy the attached folder “craftingV2” in your “cation” folder that can be found in the  root folder (subsequently called \<mission\>) of your mission.

### Step 2

Open \<mission\>/cation/cation_functions.cpp and insert

`#include "craftingV2\functions.cpp"`

and save the file.

### Step 3

Open \<mission\>/cation/cation_master.cpp and insert

`#include "craftingV2\config.cpp"`

and save the file.

### Step 4

Open \<mission\>/cation/cation_remoteExec.cpp and insert

`#include "craftingV2\remoteExec.cpp"`

and save the file.

### Step 5

Execute the following statement in your database:

```
CREATE TABLE IF NOT EXISTS `crafting` (
    `playerid` varchar(17) NOT NULL,
    `civ_plans` text NOT NULL,
    `cop_plans` text NOT NULL,
    `med_plans` text NOT NULL,
    `east_plans` text NOT NULL,
    `civ_points` int(7) NOT NULL DEFAULT '0'
    `cop_points` int(7) NOT NULL DEFAULT '0',
    `med_points` int(7) NOT NULL DEFAULT '0',
    `east_points` int(7) NOT NULL DEFAULT '0',
    `last_updated` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (`playerid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

### Step 6

Open \<mission\>/stringtable.xml and search for the line

`<Package name="Life_Items">`

and insert below the following block

```
<Key ID="STR_PLAN_COPPER">
    <Original>Copper Blueprint</Original>
    <German>Bauplan für Kupfer</German>
</Key>
<Key ID="STR_PLAN_DIAMOND">
    <Original>Diamond Blueprint</Original>
    <German>Bauplan für Diamant</German>
</Key>
<Key ID="STR_Item_SuperCrazyWeapon">
    <Original>Super Crazy Weapon</Original>
    <German>Super verrückte Waffe</German>
</Key>
```

and save the file.

### Step 7

Open \<mission\>/config/Config_vItems.hpp and search for the line

`class VirtualItems {`

and insert below the following line

`#include "..\cation\craftingV2\config\plans.cpp"`

and save the file.

### Step 8 (from version 5 of 25.12.2019)

Open \<mission\>/core/pmenu/fn_useItem.sqf and search for the line

`switch (_item) do {`

and insert before the line the following code

```
private _craftingPlans = [];
{
    private _variable = getText(_x >> "variable");
    _craftingPlans pushBack _variable;
} forEach ("true" configClasses (missionConfigFile >> "Cation_CraftingV2" >> "plans"));
 
if (_item in _craftingPlans) exitWith {
    if ([false,_item,1] call life_fnc_handleInv) then {
        [_item,true] call cat_craftingV2_fnc_handlePlan;
    };
};
```

and save the file.

### Step 8 (until version 5 of 24.12.2019)

Open \<mission\>/core/pmenu/fn_useItem.sqf and search for the line

`switch (true) do {`

and insert before the line the following code

```
private _craftingPlans = [];
{
    private _variable = getText(_x >> "variable");
    _craftingPlans pushBack _variable;
} forEach ("true" configClasses (missionConfigFile >> "Cation_CraftingV2" >> "plans"));
 
switch (true) do {
    case (_item in _craftingPlans): {
        if ([false,_item,1] call life_fnc_handleInv) then {
            [_item,true] call cat_craftingV2_fnc_handlePlan;
        };
    };
```

and save the file.

### Step 9

The base installation is now finished. To randomly drop blueprints for items you can use the following function call:

`[CHANCE,MINRARITY,MAXRARITY] call cat_craftingV2_fnc_randomPlan;`

*CHANCE* = Drop chance: Integer between 1 and 100 (corresponds to 1% to 100% drop chance of blueprint).

*MINRARITY* = Minimal rarity of dropped blueprint: Integer starting with 0 (Rarities are defined in \<mission\>/cation/craftingV2/config/rarities.cpp).

*MAXRARITY* = Maximum rarity of dropped blueprint: Integer starting with 0 (Rarities are defined in \<mission\>/cation/craftingV2/config/rarities.cpp).

**Examples**

In the following you will find a “few examples” that will give you an idea how and where to use the function call:

- *Fisching*

Open \<mission\>/core/actions/fn_dpFisch.sqf and insert at the bottom

`[50,2] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Gathering*

Open \<mission\>/core/actions/fn_gather.sqf and search for the line

`if ([true,_resource,_diff] call life_fnc_handleInv) then {`

and insert below the following line

`[20,0,1] call cat_craftingV2_fnc_randomPlan;`

and save the file.

*- Gutting animals*

Open \<mission\>/core/actions/fn_gutAnimal.sqf and search for the line

`if ([true,_item,1] call life_fnc_handleInv) then {`

and insert below the following line

`[60,0,5] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Impounding vehicles*

Open \<mission\>/core/actions/fn_impoundAction.sqf and search for the line

`hint format [localize "STR_NOTF_Impounded",_type,[_value] call life_fnc_numberText];`

and insert below the following line

`[30,0,3] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Mining*

Open \<mission\>/core/actions/fn_mine.sqf and search for the line

`if (([true, _mined, _diff] call life_fnc_handleInv)) then {`

and insert below the following line

`[20,0,1] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Bounty hunting*

Open \<mission\>/core/cop/fn_bountyReceive.sqf and insert at the bottom

`[] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Questioning drug dealer*

Open \<mission\>/core/cop/fn_questionDealer.sqf and insert at the bottom

`[30,0,1] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Repairing doors*

Open \<mission\>/core/cop/fn_repairDoor.sqf and insert at the bottom

`[40,2] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Defusing bombs`

Open \<mission\>/core/cop/fn_defuseKit.sqf and insert at the bottom

`[90,2] call cat_craftingV2_fnc_randomPlan;`

and save the file.

- *Reviving players*

Open \<mission\>/core/medic/fn_revivePlayer.sqf and insert at the bottom

`[75,2] call cat_craftingV2_fnc_randomPlan;`

and save the file.

**That's it!**

You have installed the cationstudio crafting system successfully!

## Configuration

### Basic Configuration

You can adjust basic settings in \<mission\>/cation/craftingV2/config.cpp.

In the settings it is important to set ArmA Life version to your used version.

### Texts

Texts and translations can be edited in \<mission\>/cation/craftingV2/config/language.cpp.

### Categories

The crafting categories can be set in \<mission\>/cation/craftingV2/config/categories.cpp. In this config file you will find an example with a short description. The example can be duplicated and adjusted by your needs.

### Level

The crafting levels can be set in \<mission\>/cation/craftingV2/config/levels.cpp. In this config file you will find an example with a short description. The example can be duplicated and adjusted by your needs too.

### Blue prints

The crafting blue prints can be adjusted in \<mission\>/cation/craftingV2/config/plans.cpp. In this config file you will find some examples with short descriptions. These examples can be duplicated and adjusted by your needs too.

### Rarities of blue prints

Rarities of blue prints can be set in \<mission\>/cation/craftingV2/config/rarities.cpp. In this config file you will find some examples with short descriptions. These examples can be duplicated and adjusted by your needs too.

### Crafting stations

Crafting stations can be created in \<mission\>/cation/craftingV2/config/stations.cpp. In this config file you will find some examples with short descriptions. These examples can be duplicated and adjusted by your needs too.

### How to open crafting system in-game

The crafting system can opened in-game in two different ways:

1. Via *addAction* in the init of an object on the map (mission.sqm). Init Code:

```
this allowDamage false;
this enableSimulation false;
this addAction[(["Title"] call cat_craftingV2_fnc_getText),{["CRAFTINGSTATION"] call cat_craftingV2_fnc_initDialog}];
```

**Example**

![craftingV2 addAction example](https://i.imgur.com/KL7VaNm.png)

2. Via *Button*, for examlple in your y-menu. onButtonClick code:

`onButtonClick = "closeDialog 0; [""CRAFTINGSTATION""] call cat_craftingV2_fnc_initDialog;";`

In both cases you have to pass the attribute that defines the opened crafting stations. This attribut must be a class name of a class defined in \<mission\>/cation/craftingV2/config/stations.cpp. For example if a station class is defined as follows:

```
class craftingItems {
    spawnmarker = ""; // name of marker where vehicle should spawn. Must be available on map
    categories[] = {"item","weapon"}; // defined in categories.cpp: enter classnames
};
```

the string attribute *CRAFTINGSTATION* has to be replaced with *craftingItems*.