#include "phantom_slider_joint_3d.h"

#include "../jolt_physics_server_3d.h"

#include "core/object/class_db.h"
#include "core/typedefs.h"


namespace {

using ServerParam = PhysicsServer3D::SliderJointParam;
using ServerParamJolt = JoltPhysicsServer3D::SliderJointParamJolt;
using ServerFlagJolt = JoltPhysicsServer3D::SliderJointFlagJolt;

} // namespace

void PhantomSliderJoint3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_limit_enabled"), &PhantomSliderJoint3D::get_limit_enabled);
	ClassDB::bind_method(D_METHOD("set_limit_enabled", "enabled"), &PhantomSliderJoint3D::set_limit_enabled);

	ClassDB::bind_method(D_METHOD("get_limit_upper"), &PhantomSliderJoint3D::get_limit_upper);
	ClassDB::bind_method(D_METHOD("set_limit_upper", "value"), &PhantomSliderJoint3D::set_limit_upper);

	ClassDB::bind_method(D_METHOD("get_limit_lower"), &PhantomSliderJoint3D::get_limit_lower);
	ClassDB::bind_method(D_METHOD("set_limit_lower", "value"), &PhantomSliderJoint3D::set_limit_lower);

	ClassDB::bind_method(D_METHOD("get_limit_spring_enabled"), &PhantomSliderJoint3D::get_limit_spring_enabled);
	ClassDB::bind_method(D_METHOD("set_limit_spring_enabled", "enabled"), &PhantomSliderJoint3D::set_limit_spring_enabled);

	ClassDB::bind_method(D_METHOD("get_limit_spring_frequency"), &PhantomSliderJoint3D::get_limit_spring_frequency);
	ClassDB::bind_method(D_METHOD("set_limit_spring_frequency", "value"), &PhantomSliderJoint3D::set_limit_spring_frequency);

	ClassDB::bind_method(D_METHOD("get_limit_spring_damping"), &PhantomSliderJoint3D::get_limit_spring_damping);
	ClassDB::bind_method(D_METHOD("set_limit_spring_damping", "value"), &PhantomSliderJoint3D::set_limit_spring_damping);

	ClassDB::bind_method(D_METHOD("get_motor_enabled"), &PhantomSliderJoint3D::get_motor_enabled);
	ClassDB::bind_method(D_METHOD("set_motor_enabled", "enabled"), &PhantomSliderJoint3D::set_motor_enabled);

	ClassDB::bind_method(D_METHOD("get_motor_target_velocity"), &PhantomSliderJoint3D::get_motor_target_velocity);
	ClassDB::bind_method(D_METHOD("set_motor_target_velocity", "value"), &PhantomSliderJoint3D::set_motor_target_velocity);

	ClassDB::bind_method(D_METHOD("get_motor_max_force"), &PhantomSliderJoint3D::get_motor_max_force);
	ClassDB::bind_method(D_METHOD("set_motor_max_force", "value"), &PhantomSliderJoint3D::set_motor_max_force);

	ClassDB::bind_method(D_METHOD("get_applied_force"), &PhantomSliderJoint3D::get_applied_force);
	ClassDB::bind_method(D_METHOD("get_applied_torque"), &PhantomSliderJoint3D::get_applied_torque);

	ADD_GROUP("Limit", "limit_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "limit_enabled"), "set_limit_enabled", "get_limit_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_upper", PROPERTY_HINT_NONE, "suffix:m"), "set_limit_upper", "get_limit_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_lower", PROPERTY_HINT_NONE, "suffix:m"), "set_limit_lower", "get_limit_lower");

	ADD_GROUP("Limit Spring", "limit_spring_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "limit_spring_enabled"), "set_limit_spring_enabled", "get_limit_spring_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_spring_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_limit_spring_frequency", "get_limit_spring_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_spring_damping"), "set_limit_spring_damping", "get_limit_spring_damping");

	ADD_GROUP("Motor", "motor_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "motor_enabled"), "set_motor_enabled", "get_motor_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motor_target_velocity", PROPERTY_HINT_NONE, "suffix:m/s"), "set_motor_target_velocity", "get_motor_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motor_max_force", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m/s\u00B2 (N)"), "set_motor_max_force", "get_motor_max_force");
}

void PhantomSliderJoint3D::set_limit_enabled(bool p_enabled) {
	if (limit_enabled == p_enabled) {
		return;
	}

	limit_enabled = p_enabled;

	_flag_changed(FLAG_USE_LIMIT);
}

void PhantomSliderJoint3D::set_limit_upper(double p_value) {
	if (limit_upper == p_value) {
		return;
	}

	limit_upper = p_value;

	_param_changed(PARAM_LIMIT_UPPER);
}

void PhantomSliderJoint3D::set_limit_lower(double p_value) {
	if (limit_lower == p_value) {
		return;
	}

	limit_lower = p_value;

	_param_changed(PARAM_LIMIT_LOWER);
}

void PhantomSliderJoint3D::set_limit_spring_enabled(bool p_enabled) {
	if (limit_spring_enabled == p_enabled) {
		return;
	}

	limit_spring_enabled = p_enabled;

	_flag_changed(FLAG_USE_LIMIT_SPRING);
}

void PhantomSliderJoint3D::set_limit_spring_frequency(double p_value) {
	if (limit_spring_frequency == p_value) {
		return;
	}

	limit_spring_frequency = p_value;

	_param_changed(PARAM_LIMIT_SPRING_FREQUENCY);
}

void PhantomSliderJoint3D::set_limit_spring_damping(double p_value) {
	if (limit_spring_damping == p_value) {
		return;
	}

	limit_spring_damping = p_value;

	_param_changed(PARAM_LIMIT_SPRING_DAMPING);
}

void PhantomSliderJoint3D::set_motor_enabled(bool p_enabled) {
	if (motor_enabled == p_enabled) {
		return;
	}

	motor_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_MOTOR);
}

void PhantomSliderJoint3D::set_motor_target_velocity(double p_value) {
	if (motor_target_velocity == p_value) {
		return;
	}

	motor_target_velocity = p_value;

	_param_changed(PARAM_MOTOR_TARGET_VELOCITY);
}

void PhantomSliderJoint3D::set_motor_max_force(double p_value) {
	if (motor_max_force == p_value) {
		return;
	}

	motor_max_force = p_value;

	_param_changed(PARAM_MOTOR_MAX_FORCE);
}

float PhantomSliderJoint3D::get_applied_force() const {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return 0.0f;
	}

	return physics_server->slider_joint_get_applied_force(rid);
}

float PhantomSliderJoint3D::get_applied_torque() const {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return 0.0f;
	}

	return physics_server->slider_joint_get_applied_torque(rid);
}

void PhantomSliderJoint3D::_configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_make_slider(
			rid,
			p_body_a->get_rid(),
			_get_body_local_transform(*p_body_a),
			p_body_b != nullptr ? p_body_b->get_rid() : RID(),
			p_body_b != nullptr ? _get_body_local_transform(*p_body_b) : get_global_transform().orthonormalized());

	_update_param(PARAM_LIMIT_UPPER);
	_update_param(PARAM_LIMIT_LOWER);

	_update_jolt_param(PARAM_LIMIT_SPRING_FREQUENCY);
	_update_jolt_param(PARAM_LIMIT_SPRING_DAMPING);
	_update_jolt_param(PARAM_MOTOR_TARGET_VELOCITY);
	_update_jolt_param(PARAM_MOTOR_MAX_FORCE);

	_update_jolt_flag(FLAG_USE_LIMIT);
	_update_jolt_flag(FLAG_USE_LIMIT_SPRING);
	_update_jolt_flag(FLAG_ENABLE_MOTOR);
}

void PhantomSliderJoint3D::_update_param(Param p_param) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return;
	}

	double *value = nullptr;

	switch (p_param) {
		case PARAM_LIMIT_UPPER: {
			value = &limit_upper;
		} break;
		case PARAM_LIMIT_LOWER: {
			value = &limit_lower;
		} break;
		case PARAM_MOTOR_TARGET_VELOCITY: {
			value = &motor_target_velocity;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}

	physics_server->slider_joint_set_param(rid, ServerParam(p_param), (real_t)*value);
}

void PhantomSliderJoint3D::_update_jolt_param(Param p_param) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return;
	}

	double *value = nullptr;

	switch (p_param) {
		case PARAM_LIMIT_SPRING_FREQUENCY: {
			value = &limit_spring_frequency;
		} break;
		case PARAM_LIMIT_SPRING_DAMPING: {
			value = &limit_spring_damping;
		} break;
		case PARAM_MOTOR_TARGET_VELOCITY: {
			value = &motor_target_velocity;
		} break;
		case PARAM_MOTOR_MAX_FORCE: {
			value = &motor_max_force;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}

	physics_server->slider_joint_set_jolt_param(rid, ServerParamJolt(p_param), *value);
}

void PhantomSliderJoint3D::_update_jolt_flag(Flag p_flag) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return;
	}

	bool *value = nullptr;

	switch (p_flag) {
		case FLAG_USE_LIMIT: {
			value = &limit_enabled;
		} break;
		case FLAG_USE_LIMIT_SPRING: {
			value = &limit_spring_enabled;
		} break;
		case FLAG_ENABLE_MOTOR: {
			value = &motor_enabled;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}

	physics_server->slider_joint_set_jolt_flag(rid, ServerFlagJolt(p_flag), *value);
}

void PhantomSliderJoint3D::_param_changed(Param p_param) {
	switch (p_param) {
		case PARAM_LIMIT_UPPER:
		case PARAM_LIMIT_LOWER: {
			_update_param(p_param);
		} break;
		case PARAM_LIMIT_SPRING_FREQUENCY:
		case PARAM_LIMIT_SPRING_DAMPING:
		case PARAM_MOTOR_TARGET_VELOCITY:
		case PARAM_MOTOR_MAX_FORCE: {
			_update_jolt_param(p_param);
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}
}

void PhantomSliderJoint3D::_flag_changed(Flag p_flag) {
	switch (p_flag) {
		case FLAG_USE_LIMIT:
		case FLAG_USE_LIMIT_SPRING:
		case FLAG_ENABLE_MOTOR: {
			_update_jolt_flag(p_flag);
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}
}
