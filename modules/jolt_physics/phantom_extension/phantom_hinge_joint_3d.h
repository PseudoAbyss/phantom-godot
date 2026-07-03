#pragma once

#include "../jolt_physics_server_3d.h"
#include "phantom_joint_3d.h"

class PhantomHingeJoint3D final : public PhantomJoint3D {
	GDCLASS(PhantomHingeJoint3D, PhantomJoint3D)

public:
	// clang-format off

	enum Param {
		PARAM_LIMIT_UPPER = PhysicsServer3D::HINGE_JOINT_LIMIT_UPPER,
		PARAM_LIMIT_LOWER = PhysicsServer3D::HINGE_JOINT_LIMIT_LOWER,
		PARAM_LIMIT_SPRING_FREQUENCY = JoltPhysicsServer3D::HINGE_JOINT_LIMIT_SPRING_FREQUENCY,
		PARAM_LIMIT_SPRING_DAMPING = JoltPhysicsServer3D::HINGE_JOINT_LIMIT_SPRING_DAMPING,
		PARAM_MOTOR_TARGET_VELOCITY = PhysicsServer3D::HINGE_JOINT_MOTOR_TARGET_VELOCITY,
		PARAM_MOTOR_MAX_TORQUE = JoltPhysicsServer3D::HINGE_JOINT_MOTOR_MAX_TORQUE,
		PARAM_SPRING_FREQUENCY = JoltPhysicsServer3D::HINGE_JOINT_SPRING_FREQUENCY,
		PARAM_SPRING_STIFFNESS = JoltPhysicsServer3D::HINGE_JOINT_SPRING_STIFFNESS,
		PARAM_SPRING_DAMPING = JoltPhysicsServer3D::HINGE_JOINT_SPRING_DAMPING,
	};

	enum Flag {
		FLAG_USE_LIMIT = PhysicsServer3D::HINGE_JOINT_FLAG_USE_LIMIT,
		FLAG_USE_LIMIT_SPRING = JoltPhysicsServer3D::HINGE_JOINT_FLAG_USE_LIMIT_SPRING,
		FLAG_ENABLE_MOTOR = PhysicsServer3D::HINGE_JOINT_FLAG_ENABLE_MOTOR,
		FLAG_ENABLE_SPRING = JoltPhysicsServer3D::HINGE_JOINT_FLAG_ENABLE_SPRING,
		FLAG_ENABLE_SPRING_FREQUENCY = JoltPhysicsServer3D::HINGE_JOINT_FLAG_ENABLE_SPRING_FREQUENCY,
	};

	// clang-format on

protected:
	static void _bind_methods();

public:
	bool get_limit_enabled() const { return limit_enabled; }

	void set_limit_enabled(bool p_enabled);

	double get_limit_upper() const { return limit_upper; }

	void set_limit_upper(double p_value);

	double get_limit_lower() const { return limit_lower; }

	void set_limit_lower(double p_value);

	bool get_limit_spring_enabled() const { return limit_spring_enabled; }

	void set_limit_spring_enabled(bool p_enabled);

	double get_limit_spring_frequency() const { return limit_spring_frequency; }

	void set_limit_spring_frequency(double p_value);

	double get_limit_spring_damping() const { return limit_spring_damping; }

	void set_limit_spring_damping(double p_value);

	bool get_motor_enabled() const { return motor_enabled; }

	void set_motor_enabled(bool p_enabled);

	bool get_spring_enabled() const { return spring_enabled; }

	void set_spring_enabled(bool p_enabled);

	bool get_spring_frequency_enabled() const { return spring_use_frequency; }

	void set_spring_frequency_enabled(bool p_enabled);

	double get_motor_target_velocity() const { return motor_target_velocity; }

	void set_motor_target_velocity(double p_value);

	double get_motor_max_torque() const { return motor_max_torque; }

	void set_motor_max_torque(double p_value);

	double get_spring_frequency() const { return spring_frequency; }

	void set_spring_frequency(double p_value);

	double get_spring_stiffness() const { return spring_stiffness; }

	void set_spring_stiffness(double p_value);

	double get_spring_damping() const { return spring_damping; }

	void set_spring_damping(double p_value);

	float get_applied_force() const;

	float get_applied_torque() const;

	void set_target_rotation(Basis p_rotation);

private:
	void _configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) override;

	void _update_param(Param p_param);

	void _update_jolt_param(Param p_param);

	void _update_flag(Flag p_flag);

	void _update_jolt_flag(Flag p_flag);

	void _param_changed(Param p_param);

	void _flag_changed(Flag p_flag);

	double limit_upper = 0.0;

	double limit_lower = 0.0;

	double limit_spring_frequency = 0.0;

	double limit_spring_damping = 0.0;

	double motor_target_velocity = 0.0;

	double motor_max_torque = INFINITY;

	double spring_frequency = 0.0;

	double spring_stiffness = 0.0;

	double spring_damping = 0.0;

	bool limit_enabled = false;

	bool limit_spring_enabled = false;

	bool motor_enabled = false;

	bool spring_enabled = false;

	bool spring_use_frequency = true;
};
