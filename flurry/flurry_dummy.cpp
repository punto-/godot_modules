#include "flurry.h"



void _Flurry::log_event(String p_name, Dictionary p_params) {

    print_line("FLURRY: '"+p_name+"' - "+String(Variant(p_params)));
//	_log_event(p_name, p_params, false);
};

void _Flurry::log_timed_event(String p_name, Dictionary p_params) {

    print_line("FLURRY TIMED: '"+p_name+"' - "+String(Variant(p_params)));
};

void _Flurry::end_timed_event(String p_name) {

	print_line("FLURRY END TIMED: '"+p_name);
};

void _Flurry::_bind_methods() {

	ObjectTypeDB::bind_method(_MD("log_event","name", "params"),&_Flurry::log_event);
	ObjectTypeDB::bind_method(_MD("log_timed_event","name", "params"),&_Flurry::log_timed_event);
	ObjectTypeDB::bind_method(_MD("end_timed_event","name"),&_Flurry::end_timed_event);
};

_Flurry::_Flurry() {

//	ERR_FAIL_COND(!Globals::get_singleton()->has("flurry/api_key"));
//	String api_key = GLOBAL_DEF("flurry/api_key", "");
    //flurry_start_session(api_key.ascii().get_data(), NULL, NULL, 0);
};

_Flurry::~_Flurry() {

};



