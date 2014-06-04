#include "object_type_db.h"
#include "core/globals.h"
#include "flurry.h"

void register_flurry_types() {

	Globals::get_singleton()->add_singleton(Globals::Singleton("Flurry", memnew(_Flurry)));

};

void unregister_flurry_types() {

};
