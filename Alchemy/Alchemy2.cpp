#include "Alchemy2.h"

#include <span>
#include <cassert>

namespace alchemy2 {

constexpr id_t kIdFlower = 1;
constexpr id_t kIdManaPotion = 11;

const ItemDef kItems[] = {
	{
		.id = kIdFlower,
		.name = "Witch Flower",
		.flags = ItemDef::fInventory | ItemDef::fIngredient
	}, {
		.id = 2,
		.name = "Boar Fang",
		.flags = ItemDef::fInventory | ItemDef::fIngredient
	}, {
		.id = 3,
		.name = "Frog Eye",
		.flags = ItemDef::fInventory | ItemDef::fIngredient
	}, {
		.id = kIdManaPotion,
		.name = "Potion of Mana",
		.flags = ItemDef::fInventory
	}, {
		.id = 13,
		.name = "Big Potion of Mana",
		.flags = ItemDef::fInventory
	}, {
		.id = 12,
		.name = "Potion of Health",
		.flags = ItemDef::fInventory
	}
};

const CraftRule kRules[] = {
	{
		.ingredients = { kIdFlower, 2 },
		.result = kIdManaPotion
	}, {
		.ingredients = { 1, 1, 2 },
		.result = 13
	}, {
		.ingredients = { 2, 3 },
		.result = 12
	}
};

id_t mix(std::vector<id_t> ingredients) 
{
	int nIngredients = static_cast<int>(std::ssize(ingredients));
	if (nIngredients > CraftRule::kIngredientsMax)
		return kIdUndef;

	std::sort(ingredients.begin(), ingredients.end(), std::less());

	const auto rules = std::span(kRules);
	const auto it = std::find_if(rules.begin(), rules.end(),
		[&ingredients = std::as_const(ingredients), nIngredients](const CraftRule& rule) {

			int i = 0;
			for (; i < std::min(CraftRule::kIngredientsMax, nIngredients); ++i) {
				if (rule.ingredients[i] != ingredients[i])
					return false;
			}

			return i == CraftRule::kIngredientsMax || rule.ingredients[i] == kIdUndef;
		});

	return it != rules.end() ? it->result : kIdUndef;
}

int main()
{
	std::vector<id_t> ingredients;
	ingredients.push_back(1);
	ingredients.push_back(2);
	ingredients.push_back(1);
	id_t result = mix(ingredients);

	if (result == kIdUndef) {
		std::cout << "BOOM!" << std::endl;
	}
	else {
		auto it = std::find_if(kItems, kItems + std::size(kItems), [result](const ItemDef& item) {
			return item.id == result;
		});
		assert(it != kItems + std::size(kItems));
		std::cout << it->name << std::endl;
	}

	return 0;
}

}