def can_build(plat):
	#return plat!="android" #plat == 'iphone' or plat == 'playbook'
	return True

def configure(env):

	import string
	if env['platform'] == "playbook":

		env.Append(LIBPATH=['#modules/flurry/bps/Flurry/$qnx_target_ver', '$QNX_TARGET/$qnx_target_ver/usr/lib/qt4/lib'])
		env.Append(LIBS=string.split("cpp QtCore curl crypto packageinfo bbdevice")) # holy shit
		env.Append(LIBS=['Flurry'])

	elif env['platform'] == "iphone": # iphone
		env.Append(LIBPATH=['#modules/flurry/ios'])
		env.Append(LIBS=['Flurry'])

	elif env['platform'] == 'android':
		env.android_module_library("android/FlurryAgent.jar")
		env.android_module_file("android/GodotFlurry.java")
		env.disable_module()
