#pragma once

#include <iostream>
#include <cstdint>
#include <array>
#include <string>
#include <vector>
#include <algorithm>

namespace alchemy2 {

typedef int32_t id_t;
constexpr id_t kIdUndef = 0;

struct ItemDef {

	typedef enum Flags {
		fInventory = 0x01,
		fIngredient = 0x02,
	} flags_t;

	id_t id;
	std::string name;
	uint32_t flags;

	bool isInventory() const {
		return flags & fInventory;
	}

	bool isIngredient() const {
		return flags & fIngredient;
	}

};


struct CraftRule {
	constexpr static int kIngredientsMax = 4;

	std::array<id_t, kIngredientsMax> ingredients; // should be sorted on definition
	id_t result;
};


struct Inventory {
	constexpr static int kNumSlots = 8;
	constexpr static int kStackMax = 4;

	struct Slot {
		id_t itemId;
		int count;
	};

	std::array<Slot, kNumSlots> items;
};

extern const ItemDef kItems[];
extern const CraftRule kRules[];

id_t mix(std::vector<id_t> ingredients);

int main();

}