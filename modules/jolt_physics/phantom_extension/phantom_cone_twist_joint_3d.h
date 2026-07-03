#pragma once

#include "../jolt_physics_server_3d.h"
#include "phantom_joint_3d.h"
#include "servers/physics_3d/physics_server_3d.h"

class PhantomConeTwistJoint3D final : public PhantomJoint3D {
	GDCLASS(PhantomConeTwistJoint3D, PhantomJoint3D)

public:
	// clang-format off

	enum Param {
		PARAM_SWING_LIMIT_SPAN = PhysicsServer3D::CONE_TWIST_JOINT_SWING_SPAN,
		PARAM_TWIST_LIMIT_SPAN = PhysicsServer3D::CONE_TWIST_JOINT_TWIST_SPAN,
		PARAM_SWING_LIMIT_SHIFT_Y = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_LIMIT_SHIFT_Y,
		PARAM_SWING_LIMIT_SHIFT_Z = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_LIMIT_SHIFT_Z,
		PARAM_TWIST_LIMIT_SHIFT = JoltPhysicsServer3D::CONE_TWIST_JOINT_TWIST_LIMIT_SHIFT,
		PARAM_SWING_MOTOR_TARGET_VELOCITY_Y = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_MOTOR_TARGET_VELOCITY_Y,
		PARAM_SWING_MOTOR_TARGET_VELOCITY_Z = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_MOTOR_TARGET_VELOCITY_Z,
		PARAM_TWIST_MOTOR_TARGET_VELOCITY = JoltPhysicsServer3D::CONE_TWIST_JOINT_TWIST_MOTOR_TARGET_VELOCITY,
		PARAM_SWING_MOTOR_MAX_TORQUE = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_MOTOR_MAX_TORQUE,
		PARAM_TWIST_MOTOR_MAX_TORQUE = JoltPhysicsServer3D::CONE_TWIST_JOINT_TWIST_MOTOR_MAX_TORQUE,
		PARAM_SWING_SPRING_FREQUENCY = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_SPRING_FREQUENCY,
		PARAM_SWING_SPRING_STIFFNESS = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_SPRING_STIFFNESS,
		PARAM_SWING_SPRING_DAMPING = JoltPhysicsServer3D::CONE_TWIST_JOINT_SWING_SPRING_DAMPING,
		PARAM_TWIST_SPRING_FREQUENCY = JoltPhysicsServer3D::CONE_TWIST_JOINT_TWIST_SPRING_FREQUENCY,
		PARAM_TWIST_SPRING_STIFFNESS = JoltPhysicsServer3D::CONE_TWIST_JOINT_TWIST_SPRING_STIFFNESS,
		PARAM_TWIST_SPRING_DAMPING = JoltPhysicsServer3D::CONE_TWIST_JOINT_TWIST_SPRING_DAMPING,
	};

	enum Flag {
		FLAG_USE_SWING_LIMIT = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_USE_SWING_LIMIT,
		FLAG_USE_TWIST_LIMIT = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_USE_TWIST_LIMIT,
		FLAG_ENABLE_SWING_MOTOR = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_ENABLE_SWING_MOTOR,
		FLAG_ENABLE_TWIST_MOTOR = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_ENABLE_TWIST_MOTOR,
		FLAG_ENABLE_SWING_SPRING = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_ENABLE_SWING_SPRING,
		FLAG_ENABLE_TWIST_SPRING = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_ENABLE_TWIST_SPRING,
		FLAG_ENABLE_SWING_SPRING_FREQUENCY = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_ENABLE_SWING_SPRING_FREQUENCY,
		FLAG_ENABLE_TWIST_SPRING_FREQUENCY = JoltPhysicsServer3D::CONE_TWIST_JOINT_FLAG_ENABLE_TWIST_SPRING_FREQUENCY
	};

	// clang-format on

protected:
	static void _bind_methods();

public:
	bool get_swing_limit_enabled() const { return swing_limit_enabled; }

	void set_swing_limit_enabled(bool p_enabled);

	bool get_twist_limit_enabled() const { return twist_limit_enabled; }

	void set_twist_limit_enabled(bool p_enabled);

	double get_swing_limit_span() const { return swing_limit_span; }

	void set_swing_limit_span(double p_value);

	double get_twist_limit_span() const { return twist_limit_span; }

	void set_twist_limit_span(double p_value);

	double get_swing_limit_shift_y() const { return swing_limit_shift_y; }

	void set_swing_limit_shift_y(double p_value);

	double get_swing_limit_shift_z() const { return swing_limit_shift_z; }

	void set_swing_limit_shift_z(double p_value);

	double get_twist_limit_shift() const { return twist_limit_shift; }

	void set_twist_limit_shift(double p_value);

	bool get_swing_motor_enabled() const { return swing_motor_enabled; }

	void set_swing_motor_enabled(bool p_enabled);

	bool get_twist_motor_enabled() const { return twist_motor_enabled; }

	void set_twist_motor_enabled(bool p_enabled);

	bool get_swing_spring_enabled() const { return swing_spring_enabled; }

	void set_swing_spring_enabled(bool p_enabled);

	bool get_twist_spring_enabled() const { return twist_spring_enabled; }

	void set_twist_spring_enabled(bool p_enabled);

	bool get_swing_spring_frequency_enabled() const { return swing_spring_frequency_enabled; }

	void set_swing_spring_frequency_enabled(bool p_enabled);

	bool get_twist_spring_frequency_enabled() const { return twist_spring_frequency_enabled; }

	void set_twist_spring_frequency_enabled(bool p_enabled);

	double get_swing_motor_target_velocity_y() const { return swing_motor_target_velocity_y; }

	void set_swing_motor_target_velocity_y(double p_value);

	double get_swing_motor_target_velocity_z() const { return swing_motor_target_velocity_z; }

	void set_swing_motor_target_velocity_z(double p_value);

	double get_twist_motor_target_velocity() const { return twist_motor_target_velocity; }

	void set_twist_motor_target_velocity(double p_value);

	double get_swing_motor_max_torque() const { return swing_motor_max_torque; }

	void set_swing_motor_max_torque(double p_value);

	double get_twist_motor_max_torque() const { return twist_motor_max_torque; }

	void set_twist_motor_max_torque(double p_value);

	double get_swing_spring_frequency() const { return swing_spring_frequency; }

	void set_swing_spring_frequency(double p_value);

	double get_swing_spring_stiffness() const { return swing_spring_stiffness; }

	void set_swing_spring_stiffness(double p_value);

	double get_swing_spring_damping() const { return swing_spring_damping; }

	void set_swing_spring_damping(double p_value);

	double get_twist_spring_frequency() const { return twist_spring_frequency; }

	void set_twist_spring_frequency(double p_value);

	double get_twist_spring_stiffness() const { return twist_spring_stiffness; }

	void set_twist_spring_stiffness(double p_value);

	double get_twist_spring_damping() const { return twist_spring_damping; }

	void set_twist_spring_damping(double p_value);

	float get_applied_force() const;

	float get_applied_torque() const;

	void set_target_rotation(Basis p_rotation);

private:
	void _configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) override;

	void _update_param(Param p_param);

	void _update_jolt_param(Param p_param);

	void _update_jolt_flag(Flag p_flag);

	void _param_changed(Param p_param);

	void _flag_changed(Flag p_flag);

	double swing_limit_span = 0.0f;

	double twist_limit_span = 0.0f;

	double swing_limit_shift_y = 0.0f;

	double swing_limit_shift_z = 0.0f;

	double twist_limit_shift = 0.0f;

	double swing_motor_target_velocity_y = 0.0;

	double swing_motor_target_velocity_z = 0.0;

	double twist_motor_target_velocity = 0.0;

	double swing_motor_max_torque = INFINITY;

	double twist_motor_max_torque = INFINITY;

	double swing_spring_frequency = 0.0;

	double swing_spring_stiffness = 0.0;

	double swing_spring_damping = 0.0;

	double twist_spring_frequency = 0.0;

	double twist_spring_stiffness = 0.0;

	double twist_spring_damping = 0.0;

	bool swing_limit_enabled = false;

	bool twist_limit_enabled = false;

	bool swing_motor_enabled = false;

	bool twist_motor_enabled = false;

	bool swing_spring_enabled = false;

	bool twist_spring_enabled = false;

	bool swing_spring_frequency_enabled = true;

	bool twist_spring_frequency_enabled = true;
};