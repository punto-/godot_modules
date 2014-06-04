#include "flurry.h"

#include "core/globals.h"
#import "ios/Flurry.h"

static void _log_event(String p_name, const Dictionary &p_params, bool p_timed) {

	NSString *nsname = [NSString stringWithUTF8String:p_name.utf8().get_data()];

	if (p_params.size() == 0) {

		[Flurry logEvent:nsname];
		return;
	};

	NSMutableDictionary* nsparams = [NSMutableDictionary dictionaryWithCapacity: p_params.size()];
	Array keys = p_params.keys();
	for (int i=0; i<keys.size(); i++) {

		NSString *nskey = [NSString stringWithUTF8String:String(keys[i]).utf8().get_data()];
		NSString *nsval = [NSString stringWithUTF8String:String(p_params[keys[i]]).utf8().get_data()];

		[nsparams setObject:nskey forKey:nsval];
	};

	[Flurry logEvent:nsname withParameters:nsparams];
};
void _Flurry::log_event(String p_name, Dictionary p_params) {

	_log_event(p_name, p_params, false);
};

void _Flurry::log_timed_event(String p_name, Dictionary p_params) {

	_log_event(p_name, p_params, true);
};

void _Flurry::end_timed_event(String p_name) {

	NSString *nsname = [NSString stringWithUTF8String:p_name.utf8().get_data()];
	[Flurry endTimedEvent:nsname withParameters:nil];
};

void _Flurry::_bind_methods() {

	ObjectTypeDB::bind_method(_MD("log_event","name", "params"),&_Flurry::log_event);
	ObjectTypeDB::bind_method(_MD("log_timed_event","name", "params"),&_Flurry::log_timed_event);
	ObjectTypeDB::bind_method(_MD("end_timed_event","name"),&_Flurry::end_timed_event);
};

_Flurry::_Flurry() {

	ERR_FAIL_COND(!Globals::get_singleton()->has("flurry/api_key"));
	String api_key = GLOBAL_DEF("flurry/api_key", "");
	NSString *nskey = [NSString stringWithUTF8String:api_key.utf8().get_data()];
	[Flurry startSession:nskey];
};

_Flurry::~_Flurry() {

};

