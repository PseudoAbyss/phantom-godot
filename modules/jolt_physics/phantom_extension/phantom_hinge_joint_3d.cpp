#include "phantom_hinge_joint_3d.h"

#include "../jolt_physics_server_3d.h"

#include "core/object/class_db.h"


namespace {

using ServerParam = PhysicsServer3D::HingeJointParam;
using ServerFlag = PhysicsServer3D::HingeJointFlag;
using ServerParamJolt = JoltPhysicsServer3D::HingeJointParamJolt;
using ServerFlagJolt = JoltPhysicsServer3D::HingeJointFlagJolt;

} // namespace

void PhantomHingeJoint3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_limit_enabled"), &PhantomHingeJoint3D::get_limit_enabled);
	ClassDB::bind_method(D_METHOD("set_limit_enabled", "enabled"), &PhantomHingeJoint3D::set_limit_enabled);

	ClassDB::bind_method(D_METHOD("get_limit_upper"), &PhantomHingeJoint3D::get_limit_upper);
	ClassDB::bind_method(D_METHOD("set_limit_upper", "value"), &PhantomHingeJoint3D::set_limit_upper);

	ClassDB::bind_method(D_METHOD("get_limit_lower"), &PhantomHingeJoint3D::get_limit_lower);
	ClassDB::bind_method(D_METHOD("set_limit_lower", "value"), &PhantomHingeJoint3D::set_limit_lower);

	ClassDB::bind_method(D_METHOD("get_limit_spring_enabled"), &PhantomHingeJoint3D::get_limit_spring_enabled);
	ClassDB::bind_method(D_METHOD("set_limit_spring_enabled", "enabled"), &PhantomHingeJoint3D::set_limit_spring_enabled);

	ClassDB::bind_method(D_METHOD("get_limit_spring_frequency"), &PhantomHingeJoint3D::get_limit_spring_frequency);
	ClassDB::bind_method(D_METHOD("set_limit_spring_frequency", "value"), &PhantomHingeJoint3D::set_limit_spring_frequency);

	ClassDB::bind_method(D_METHOD("get_limit_spring_damping"), &PhantomHingeJoint3D::get_limit_spring_damping);
	ClassDB::bind_method(D_METHOD("set_limit_spring_damping", "value"), &PhantomHingeJoint3D::set_limit_spring_damping);

	ClassDB::bind_method(D_METHOD("get_motor_enabled"), &PhantomHingeJoint3D::get_motor_enabled);
	ClassDB::bind_method(D_METHOD("set_motor_enabled", "enabled"), &PhantomHingeJoint3D::set_motor_enabled);

	ClassDB::bind_method(D_METHOD("get_motor_target_velocity"), &PhantomHingeJoint3D::get_motor_target_velocity);
	ClassDB::bind_method(D_METHOD("set_motor_target_velocity", "value"), &PhantomHingeJoint3D::set_motor_target_velocity);

	ClassDB::bind_method(D_METHOD("get_motor_max_torque"), &PhantomHingeJoint3D::get_motor_max_torque);
	ClassDB::bind_method(D_METHOD("set_motor_max_torque", "value"), &PhantomHingeJoint3D::set_motor_max_torque);

	ClassDB::bind_method(D_METHOD("get_spring_enabled"), &PhantomHingeJoint3D::get_spring_enabled);
	ClassDB::bind_method(D_METHOD("set_spring_enabled", "enabled"), &PhantomHingeJoint3D::set_spring_enabled);

	ClassDB::bind_method(D_METHOD("get_spring_frequency_enabled"), &PhantomHingeJoint3D::get_spring_frequency_enabled);
	ClassDB::bind_method(D_METHOD("set_spring_frequency_enabled", "enabled"), &PhantomHingeJoint3D::set_spring_frequency_enabled);

	ClassDB::bind_method(D_METHOD("get_spring_frequency"), &PhantomHingeJoint3D::get_spring_frequency);
	ClassDB::bind_method(D_METHOD("set_spring_frequency", "value"), &PhantomHingeJoint3D::set_spring_frequency);

	ClassDB::bind_method(D_METHOD("get_spring_stiffness"), &PhantomHingeJoint3D::get_spring_stiffness);
	ClassDB::bind_method(D_METHOD("set_spring_stiffness", "value"), &PhantomHingeJoint3D::set_spring_stiffness);

	ClassDB::bind_method(D_METHOD("get_spring_damping"), &PhantomHingeJoint3D::get_spring_damping);
	ClassDB::bind_method(D_METHOD("set_spring_damping", "value"), &PhantomHingeJoint3D::set_spring_damping);

	ClassDB::bind_method(D_METHOD("get_applied_force"), &PhantomHingeJoint3D::get_applied_force);
	ClassDB::bind_method(D_METHOD("get_applied_torque"), &PhantomHingeJoint3D::get_applied_torque);

	ClassDB::bind_method(D_METHOD("set_target_rotation", "rotation"), &PhantomHingeJoint3D::set_target_rotation);

	ADD_GROUP("Limit", "limit_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "limit_enabled"), "set_limit_enabled", "get_limit_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_upper", PROPERTY_HINT_RANGE, "-180,180,0.1,radians_as_degrees"), "set_limit_upper", "get_limit_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_lower", PROPERTY_HINT_RANGE, "-180,180,0.1,radians_as_degrees"), "set_limit_lower", "get_limit_lower");

	ADD_GROUP("Limit Spring", "limit_spring_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "limit_spring_enabled"), "set_limit_spring_enabled", "get_limit_spring_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_spring_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_limit_spring_frequency", "get_limit_spring_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "limit_spring_damping"), "set_limit_spring_damping", "get_limit_spring_damping");

	ADD_GROUP("Motor", "motor_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "motor_enabled"), "set_motor_enabled", "get_motor_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motor_target_velocity", PROPERTY_HINT_NONE, U"radians_as_degrees,suffix:°/s"), "set_motor_target_velocity", "get_motor_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "motor_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_motor_max_torque", "get_motor_max_torque");

	ADD_GROUP("Spring", "spring_");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "spring_enabled"), "set_spring_enabled", "get_spring_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "spring_frequency_enabled"), "set_spring_frequency_enabled", "get_spring_frequency_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_frequency", PROPERTY_HINT_NONE, ""), "set_spring_frequency", "get_spring_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_stiffness", PROPERTY_HINT_NONE, ""), "set_spring_stiffness", "get_spring_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spring_damping", PROPERTY_HINT_NONE, ""), "set_spring_damping", "get_spring_damping");
}

void PhantomHingeJoint3D::set_limit_enabled(bool p_enabled) {
	if (limit_enabled == p_enabled) {
		return;
	}

	limit_enabled = p_enabled;

	_flag_changed(FLAG_USE_LIMIT);
}

void PhantomHingeJoint3D::set_limit_upper(double p_value) {
	if (limit_upper == p_value) {
		return;
	}

	limit_upper = p_value;

	_param_changed(PARAM_LIMIT_UPPER);
}

void PhantomHingeJoint3D::set_limit_lower(double p_value) {
	if (limit_lower == p_value) {
		return;
	}

	limit_lower = p_value;

	_param_changed(PARAM_LIMIT_LOWER);
}

void PhantomHingeJoint3D::set_limit_spring_enabled(bool p_enabled) {
	if (limit_spring_enabled == p_enabled) {
		return;
	}

	limit_spring_enabled = p_enabled;

	_flag_changed(FLAG_USE_LIMIT_SPRING);
}

void PhantomHingeJoint3D::set_limit_spring_frequency(double p_value) {
	if (limit_spring_frequency == p_value) {
		return;
	}

	limit_spring_frequency = p_value;

	_param_changed(PARAM_LIMIT_SPRING_FREQUENCY);
}

void PhantomHingeJoint3D::set_limit_spring_damping(double p_value) {
	if (limit_spring_damping == p_value) {
		return;
	}

	limit_spring_damping = p_value;

	_param_changed(PARAM_LIMIT_SPRING_DAMPING);
}

void PhantomHingeJoint3D::set_motor_enabled(bool p_enabled) {
	if (motor_enabled == p_enabled) {
		return;
	}

	motor_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_MOTOR);
}

void PhantomHingeJoint3D::set_spring_enabled(bool p_enabled) {
	if (spring_enabled == p_enabled) {
		return;
	}

	spring_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_SPRING);
}

void PhantomHingeJoint3D::set_spring_frequency_enabled(bool p_enabled) {
	if (spring_use_frequency == p_enabled) {
		return;
	}

	spring_use_frequency = p_enabled;

	_flag_changed(FLAG_ENABLE_SPRING_FREQUENCY);
}

void PhantomHingeJoint3D::set_motor_target_velocity(double p_value) {
	if (motor_target_velocity == p_value) {
		return;
	}

	motor_target_velocity = p_value;

	_param_changed(PARAM_MOTOR_TARGET_VELOCITY);
}

void PhantomHingeJoint3D::set_motor_max_torque(double p_value) {
	if (motor_max_torque == p_value) {
		return;
	}

	motor_max_torque = p_value;

	_param_changed(PARAM_MOTOR_MAX_TORQUE);
}

void PhantomHingeJoint3D::set_spring_frequency(double p_value) {
	if (spring_frequency == p_value) {
		return;
	}

	spring_frequency = p_value;

	_param_changed(PARAM_SPRING_FREQUENCY);
}

void PhantomHingeJoint3D::set_spring_stiffness(double p_value) {
	if (spring_stiffness == p_value) {
		return;
	}

	spring_stiffness = p_value;

	_param_changed(PARAM_SPRING_STIFFNESS);
}

void PhantomHingeJoint3D::set_spring_damping(double p_value) {
	if (spring_damping == p_value) {
		return;
	}

	spring_damping = p_value;

	_param_changed(PARAM_SPRING_DAMPING);
}

float PhantomHingeJoint3D::get_applied_force() const {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return 0.0f;
	}

	return physics_server->hinge_joint_get_applied_force(rid);
}

float PhantomHingeJoint3D::get_applied_torque() const {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return 0.0f;
	}

	return physics_server->hinge_joint_get_applied_torque(rid);
}

void PhantomHingeJoint3D::set_target_rotation(Basis p_rotation) {
	JoltPhysicsServer3D *server = _get_jolt_physics_server();
	if (unlikely(server == nullptr)) {
		return;
	}

	server->hinge_joint_set_target_rotation(rid, p_rotation);
}

void PhantomHingeJoint3D::_configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_make_hinge(
			rid,
			p_body_a->get_rid(),
			_get_body_local_transform(*p_body_a),
			p_body_b != nullptr ? p_body_b->get_rid() : RID(),
			p_body_b != nullptr ? _get_body_local_transform(*p_body_b) : get_global_transform().orthonormalized());

	_update_param(PARAM_LIMIT_UPPER);
	_update_param(PARAM_LIMIT_LOWER);
	_update_param(PARAM_MOTOR_TARGET_VELOCITY);

	_update_jolt_param(PARAM_LIMIT_SPRING_FREQUENCY);
	_update_jolt_param(PARAM_LIMIT_SPRING_DAMPING);
	_update_jolt_param(PARAM_MOTOR_MAX_TORQUE);

	_update_flag(FLAG_USE_LIMIT);
	_update_flag(FLAG_ENABLE_MOTOR);

	_update_jolt_flag(FLAG_USE_LIMIT_SPRING);
}

void PhantomHingeJoint3D::_update_param(Param p_param) {
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

	physics_server->hinge_joint_set_param(rid, ServerParam(p_param), (real_t)*value);
}

void PhantomHingeJoint3D::_update_jolt_param(Param p_param) {
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
		case PARAM_MOTOR_MAX_TORQUE: {
			value = &motor_max_torque;
		} break;
		case PARAM_SPRING_FREQUENCY: {
			value = &spring_frequency;
		} break;
		case PARAM_SPRING_STIFFNESS: {
			value = &spring_stiffness;
		} break;
		case PARAM_SPRING_DAMPING: {
			value = &spring_damping;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}

	physics_server->hinge_joint_set_jolt_param(rid, ServerParamJolt(p_param), *value);
}

void PhantomHingeJoint3D::_update_flag(Flag p_flag) {
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
		case FLAG_ENABLE_MOTOR: {
			value = &motor_enabled;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}

	physics_server->hinge_joint_set_flag(rid, ServerFlag(p_flag), *value);
}

void PhantomHingeJoint3D::_update_jolt_flag(Flag p_flag) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return;
	}

	bool *value = nullptr;

	switch (p_flag) {
		case FLAG_USE_LIMIT_SPRING: {
			value = &limit_spring_enabled;
		} break;
		case FLAG_ENABLE_SPRING: {
			value = &spring_enabled;
		} break;
		case FLAG_ENABLE_SPRING_FREQUENCY: {
			value = &spring_use_frequency;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}

	physics_server->hinge_joint_set_jolt_flag(rid, ServerFlagJolt(p_flag), *value);
}

void PhantomHingeJoint3D::_param_changed(Param p_param) {
	switch (p_param) {
		case PARAM_LIMIT_UPPER:
		case PARAM_LIMIT_LOWER:
		case PARAM_MOTOR_TARGET_VELOCITY: {
			_update_param(p_param);
		} break;
		case PARAM_LIMIT_SPRING_FREQUENCY:
		case PARAM_LIMIT_SPRING_DAMPING:
		case PARAM_MOTOR_MAX_TORQUE:
		case PARAM_SPRING_FREQUENCY:
		case PARAM_SPRING_STIFFNESS:
		case PARAM_SPRING_DAMPING: {
			_update_jolt_param(p_param);
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}
}

void PhantomHingeJoint3D::_flag_changed(Flag p_flag) {
	switch (p_flag) {
		case FLAG_USE_LIMIT:
		case FLAG_ENABLE_MOTOR: {
			_update_flag(p_flag);
		} break;
		case FLAG_USE_LIMIT_SPRING:
		case FLAG_ENABLE_SPRING:
		case FLAG_ENABLE_SPRING_FREQUENCY: {
			_update_jolt_flag(p_flag);
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}
}
