#include "flurry.h"

#include "core/globals.h"

#include "bps/FlurryC.h"

static void _log_event(String p_name, const Dictionary &p_params, bool p_timed) {

	if (p_params.size() == 0) {

		flurry_log_event(p_name.ascii().get_data(), p_timed?1:0);
		return;
	};

	Vector<CharString> keys;
	Vector<CharString> vals;
	Array vkeys = p_params.keys();
	for (int i=0; i<vkeys.size(); i++) {

		keys.push_back(String(vkeys[i]).ascii());
		vals.push_back(String(p_params[vkeys[i]]).ascii());
	};
	const char** ckeys = (const char**)memnew_arr(char*, keys.size());
	const char** cvals = (const char**)memnew_arr(char*, vals.size());
	for (int i=0; i<keys.size(); i++) {
		ckeys[i] = keys[i].get_data();
		cvals[i] = vals[i].get_data();
	};

	flurry_log_event_with_params(p_name.ascii().get_data(), p_timed?1:0, ckeys, cvals, keys.size());

	memdelete_arr(ckeys);
	memdelete_arr(cvals);
};

void _Flurry::log_event(String p_name, Dictionary p_params) {

	_log_event(p_name, p_params, false);
};

void _Flurry::log_timed_event(String p_name, Dictionary p_params) {

	_log_event(p_name, p_params, true);
};

void _Flurry::end_timed_event(String p_name) {

	flurry_end_timed_event(p_name.ascii().get_data(), NULL, NULL, 0);
};

void _Flurry::_bind_methods() {

	ObjectTypeDB::bind_method(_MD("log_event","name", "params"),&_Flurry::log_event);
	ObjectTypeDB::bind_method(_MD("log_timed_event","name", "params"),&_Flurry::log_timed_event);
	ObjectTypeDB::bind_method(_MD("end_timed_event","name"),&_Flurry::end_timed_event);
};

_Flurry::_Flurry() {

	ERR_FAIL_COND(!Globals::get_singleton()->has("flurry/api_key"));
	String api_key = GLOBAL_DEF("flurry/api_key", "");
	flurry_start_session(api_key.ascii().get_data(), NULL, NULL, 0);
};

_Flurry::~_Flurry() {

};



