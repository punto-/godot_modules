#include "core/object.h"

class _Flurry : public Object {

	OBJ_TYPE(_Flurry, Object);

	static void _bind_methods();

public:

	void log_event(String p_name, Dictionary p_params);
	void log_timed_event(String p_name, Dictionary p_params);
	void end_timed_event(String p_name);

	_Flurry();
	~_Flurry();
};

