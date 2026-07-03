/**************************************************************************/
/*  register_types.cpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "register_types.h"

#include "jolt_globals.h"
#include "jolt_physics_server_3d.h"
#include "jolt_project_settings.h"
#include "objects/jolt_physics_direct_body_state_3d.h"
#include "phantom_extension/phantom_cone_twist_joint_3d.h"
#include "phantom_extension/phantom_editor_plugin.h"
#include "phantom_extension/phantom_generic_6dof_joint.h"
#include "phantom_extension/phantom_hinge_joint_3d.h"
#include "phantom_extension/phantom_pin_joint_3d.h"
#include "phantom_extension/phantom_slider_joint_3d.h"
#include "spaces/jolt_physics_direct_space_state_3d.h"

#include "core/config/project_settings.h"
#include "core/object/callable_mp.h"
#include "core/object/class_db.h"
#include "servers/physics_3d/physics_server_3d_wrap_mt.h"

PhysicsServer3D *create_jolt_physics_server() {
#ifdef THREADS_ENABLED
	bool run_on_separate_thread = GLOBAL_GET("physics/3d/run_on_separate_thread");
#else
	bool run_on_separate_thread = false;
#endif

	JoltPhysicsServer3D *physics_server = memnew(JoltPhysicsServer3D()); // memnew(JoltPhysicsServer3D(run_on_separate_thread));
	physics_server->set_on_separate_thread(run_on_separate_thread);

	return memnew(PhysicsServer3DWrapMT(physics_server, run_on_separate_thread));
}

void initialize_jolt_physics_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SERVERS && !MODULE_INITIALIZATION_LEVEL_SCENE && !MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}

	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_CORE: {
		} break;
		case MODULE_INITIALIZATION_LEVEL_SERVERS: {
			jolt_initialize();

			GDREGISTER_VIRTUAL_CLASS(JoltPhysicsDirectBodyState3D);
			GDREGISTER_VIRTUAL_CLASS(JoltPhysicsDirectSpaceState3D);
			GDREGISTER_VIRTUAL_CLASS(JoltPhysicsServer3D);

			PhysicsServer3DManager::get_singleton()->register_server("Jolt Physics", callable_mp_static(&create_jolt_physics_server));
			JoltProjectSettings::register_settings();
		} break;
		case MODULE_INITIALIZATION_LEVEL_SCENE: {
			JoltProjectSettings::register_settings();

			GDREGISTER_VIRTUAL_CLASS(PhantomJoint3D)
			GDREGISTER_CLASS(PhantomJoint3D);
			GDREGISTER_CLASS(PhantomPinJoint3D);
			GDREGISTER_CLASS(PhantomHingeJoint3D);
			GDREGISTER_CLASS(PhantomSliderJoint3D);
			GDREGISTER_CLASS(PhantomConeTwistJoint3D);
			GDREGISTER_CLASS(PhantomGeneric6DOFJoint3D);
		} break;
		case MODULE_INITIALIZATION_LEVEL_EDITOR: {
#if defined(TOOLS_ENABLED)
			EditorPlugins::add_by_type<PhantomEditorPlugin>();
#endif
		} break;
	}
}

void uninitialize_jolt_physics_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SERVERS) {
		return;
	}

	jolt_deinitialize();
}
