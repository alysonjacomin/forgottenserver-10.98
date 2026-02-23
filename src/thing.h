// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_THING_H
#define FS_THING_H

#include "enums.h"

class Container;
class Creature;
class Item;
class Tile;

inline constexpr int32_t INDEX_WHEREEVER = -1;

enum ReceiverFlag_t {
	FLAG_NOLIMIT = 1 << 0,             // Bypass limits like capacity/container limits, blocking items/creatures etc.
	FLAG_IGNOREBLOCKITEM = 1 << 1,     // Bypass movable blocking item checks
	FLAG_IGNOREBLOCKCREATURE = 1 << 2, // Bypass creature checks
	FLAG_CHILDISOWNER = 1 << 3,        // Used by containers to query capacity of the carrier (player)
	FLAG_PATHFINDING = 1 << 4,         // An additional check is done for floor changing/teleport items
	FLAG_IGNOREFIELDDAMAGE = 1 << 5,   // Bypass field damage checks
	FLAG_IGNORENOTMOVEABLE = 1 << 6,   // Bypass check for mobility
	FLAG_IGNOREAUTOSTACK = 1 << 7,     // queryDestination will not try to stack items together
};

enum ReceiverLink_t {
	LINK_OWNER,
	LINK_PARENT,
	LINK_TOPPARENT,
	LINK_NEAR,
};

struct Position;

class Thing {
	public:
		constexpr Thing() = default;
		virtual ~Thing() = default;

		// non-copyable
		Thing(const Thing&) = delete;
		Thing& operator=(const Thing&) = delete;

		bool hasParent() const { return getParent(); }
		virtual Thing* getParent() const { return parent; }
		Thing* getRealParent() const { return parent; }
		virtual void setParent(Thing* parent) { this->parent = parent; }

		virtual const Position& getPosition() const;
		virtual int32_t getThrowRange() const = 0;
		virtual bool isPushable() const = 0;

		virtual Thing* getReceiver() {
			return nullptr;
		}
		virtual const Thing* getReceiver() const {
			return nullptr;
		}

		virtual Item* getItem() {
			return nullptr;
		}
		virtual const Item* getItem() const {
			return nullptr;
		}
		virtual Creature* getCreature() {
			return nullptr;
		}
		virtual const Creature* getCreature() const {
			return nullptr;
		}
		virtual Tile* getTile() {
			return nullptr;
		}
		virtual const Tile* getTile() const {
			return nullptr;
		}

		virtual bool isRemoved() const {
			return true;
		}

		virtual ReturnValue queryAdd(int32_t, const Thing&, uint32_t, uint32_t, Creature* = nullptr) const { return RETURNVALUE_NOTPOSSIBLE; }
		virtual ReturnValue queryMaxCount(int32_t, const Thing&, uint32_t, uint32_t&, uint32_t) const { return RETURNVALUE_NOTPOSSIBLE; }
		virtual ReturnValue queryRemove(const Thing&, uint32_t, uint32_t, Creature* = nullptr) const { return RETURNVALUE_NOTPOSSIBLE; }
		virtual Thing* queryDestination(int32_t&, const Thing&, Item**, uint32_t&) { return nullptr; }

		virtual void addThing(Thing*) {}
		virtual void addThing(int32_t, Thing*) {}
		virtual void updateThing(Thing*, uint16_t, uint32_t) {}
		virtual void replaceThing(uint32_t, Thing*) {}
		virtual void removeThing(Thing*, uint32_t) {}

		virtual void postAddNotification(Thing*, const Thing*, int32_t, ReceiverLink_t = LINK_OWNER) {}
		virtual void postRemoveNotification(Thing*, const Thing*, int32_t, ReceiverLink_t = LINK_OWNER) {}

		virtual int32_t getThingIndex(const Thing*) const { return -1; }
		virtual size_t getFirstIndex() const { return 0; }
		virtual size_t getLastIndex() const { return 0; }

		virtual Thing* getThing(size_t) const { return nullptr; }

		virtual uint32_t getItemTypeCount(uint16_t, int32_t = -1) const { return 0; }
		virtual std::map<uint32_t, uint32_t>& getAllItemTypeCount(std::map<uint32_t, uint32_t>& countMap) const { return countMap; }

		virtual void internalRemoveThing(Thing*) {}
		virtual void internalAddThing(Thing*) {}
		virtual void internalAddThing(uint32_t, Thing*) {}

	private:
		Thing* parent = nullptr;
};

#endif // FS_THING_H