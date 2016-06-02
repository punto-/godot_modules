package org.godotengine.godot;

import android.app.Activity;
import org.godotengine.godot.Dictionary;
import com.flurry.android.FlurryAgent;
//import com.flurry.android.ads.FlurryAdBanner;
//import com.flurry.android.ads.FlurryAdBannerListener;
import java.util.HashMap;
import java.util.Map;

public class GodotFlurry extends Godot.SingletonBase {

	private boolean active=true;
	private Activity activity;

	public void _log_event(String p_name, Dictionary p_params, boolean p_timed) {

		if (!active) return;
		
		if (p_params.size() == 0) {
			FlurryAgent.logEvent(p_name, null, p_timed);
			return;
		};

		Map<String, String> params = new HashMap<String, String>();
		String[] keys = p_params.get_keys();
		for (String key : keys) {
			params.put(key, p_params.get(key).toString());
		};
		FlurryAgent.logEvent(p_name, params, p_timed);
	};

	public void log_event(String p_name, Dictionary p_params) {

		if (!active) return;

		_log_event(p_name, p_params, false);
	};

	public void log_timed_event(String p_name, Dictionary p_params) {

		if (!active) return;

		_log_event(p_name, p_params, true);
	};

	public void end_timed_event(String p_name) {


		if (!active) return;
		FlurryAgent.endTimedEvent(p_name);
	};

	static public Godot.SingletonBase initialize(Activity p_activity) {

		return new GodotFlurry(p_activity);
	}

	public GodotFlurry(Activity p_activity) {
		registerClass("Flurry", new String[] {"log_event", "log_timed_event", "end_timed_event"});
		
		activity=p_activity;
		if (!active) return;

		activity.runOnUiThread(new Runnable() {
			public void run() {
				String key = GodotLib.getGlobal("flurry/api_key");
				FlurryAgent.init(activity, key);
//				FlurryAgent.onStartSession(activity, key); on android api >= 14 onStartSession / onEndSession are handled automatically
			}
		});
	}
}
