#include "phantom_generic_6dof_joint.h"

#include "../jolt_physics_server_3d.h"

#include "core/object/class_db.h"
#include "core/typedefs.h"

namespace {

using ServerAxis = Vector3::Axis;
using ServerParam = PhysicsServer3D::G6DOFJointAxisParam;
using ServerParamJolt = JoltPhysicsServer3D::G6DOFJointAxisParamJolt;
using ServerFlag = JoltPhysicsServer3D::G6DOFJointAxisFlag;
using ServerFlagJolt = JoltPhysicsServer3D::G6DOFJointAxisFlagJolt;

} // namespace

void PhantomGeneric6DOFJoint3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_param_x", "param"), &PhantomGeneric6DOFJoint3D::get_param_x);
	ClassDB::bind_method(D_METHOD("set_param_x", "param", "value"), &PhantomGeneric6DOFJoint3D::set_param_x);

	ClassDB::bind_method(D_METHOD("get_param_y", "param"), &PhantomGeneric6DOFJoint3D::get_param_y);
	ClassDB::bind_method(D_METHOD("set_param_y", "param", "value"), &PhantomGeneric6DOFJoint3D::set_param_y);

	ClassDB::bind_method(D_METHOD("get_param_z", "param"), &PhantomGeneric6DOFJoint3D::get_param_z);
	ClassDB::bind_method(D_METHOD("set_param_z", "param", "value"), &PhantomGeneric6DOFJoint3D::set_param_z);

	ClassDB::bind_method(D_METHOD("get_flag_x", "flag"), &PhantomGeneric6DOFJoint3D::get_flag_x);
	ClassDB::bind_method(D_METHOD("set_flag_x", "flag", "enabled"), &PhantomGeneric6DOFJoint3D::set_flag_x);

	ClassDB::bind_method(D_METHOD("get_flag_y", "flag"), &PhantomGeneric6DOFJoint3D::get_flag_y);
	ClassDB::bind_method(D_METHOD("set_flag_y", "flag", "enabled"), &PhantomGeneric6DOFJoint3D::set_flag_y);

	ClassDB::bind_method(D_METHOD("get_flag_z", "flag"), &PhantomGeneric6DOFJoint3D::get_flag_z);
	ClassDB::bind_method(D_METHOD("set_flag_z", "flag", "enabled"), &PhantomGeneric6DOFJoint3D::set_flag_z);

	ClassDB::bind_method(D_METHOD("get_linear_limit_x_upper"), &PhantomGeneric6DOFJoint3D::get_linear_limit_x_upper);
	ClassDB::bind_method(D_METHOD("set_linear_limit_x_upper", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_x_upper);
	ClassDB::bind_method(D_METHOD("get_linear_limit_x_lower"), &PhantomGeneric6DOFJoint3D::get_linear_limit_x_lower);
	ClassDB::bind_method(D_METHOD("set_linear_limit_x_lower", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_x_lower);

	ClassDB::bind_method(D_METHOD("get_linear_limit_y_upper"), &PhantomGeneric6DOFJoint3D::get_linear_limit_y_upper);
	ClassDB::bind_method(D_METHOD("set_linear_limit_y_upper", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_y_upper);
	ClassDB::bind_method(D_METHOD("get_linear_limit_y_lower"), &PhantomGeneric6DOFJoint3D::get_linear_limit_y_lower);
	ClassDB::bind_method(D_METHOD("set_linear_limit_y_lower", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_y_lower);

	ClassDB::bind_method(D_METHOD("get_linear_limit_z_upper"), &PhantomGeneric6DOFJoint3D::get_linear_limit_z_upper);
	ClassDB::bind_method(D_METHOD("set_linear_limit_z_upper", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_z_upper);
	ClassDB::bind_method(D_METHOD("get_linear_limit_z_lower"), &PhantomGeneric6DOFJoint3D::get_linear_limit_z_lower);
	ClassDB::bind_method(D_METHOD("set_linear_limit_z_lower", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_z_lower);

	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_x_frequency"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_x_frequency);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_x_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_x_frequency);
	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_x_damping"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_x_damping);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_x_damping", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_x_damping);

	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_y_frequency"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_y_frequency);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_y_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_y_frequency);
	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_y_damping"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_y_damping);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_y_damping", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_y_damping);

	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_z_frequency"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_z_frequency);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_z_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_z_frequency);
	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_z_damping"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_z_damping);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_z_damping", "value"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_z_damping);

	ClassDB::bind_method(D_METHOD("get_linear_motor_x_target_velocity"), &PhantomGeneric6DOFJoint3D::get_linear_motor_x_target_velocity);
	ClassDB::bind_method(D_METHOD("set_linear_motor_x_target_velocity", "value"), &PhantomGeneric6DOFJoint3D::set_linear_motor_x_target_velocity);
	ClassDB::bind_method(D_METHOD("get_linear_motor_x_max_force"), &PhantomGeneric6DOFJoint3D::get_linear_motor_x_max_force);
	ClassDB::bind_method(D_METHOD("set_linear_motor_x_max_force", "value"), &PhantomGeneric6DOFJoint3D::set_linear_motor_x_max_force);

	ClassDB::bind_method(D_METHOD("get_linear_motor_y_target_velocity"), &PhantomGeneric6DOFJoint3D::get_linear_motor_y_target_velocity);
	ClassDB::bind_method(D_METHOD("set_linear_motor_y_target_velocity", "value"), &PhantomGeneric6DOFJoint3D::set_linear_motor_y_target_velocity);
	ClassDB::bind_method(D_METHOD("get_linear_motor_y_max_force"), &PhantomGeneric6DOFJoint3D::get_linear_motor_y_max_force);
	ClassDB::bind_method(D_METHOD("set_linear_motor_y_max_force", "value"), &PhantomGeneric6DOFJoint3D::set_linear_motor_y_max_force);

	ClassDB::bind_method(D_METHOD("get_linear_motor_z_target_velocity"), &PhantomGeneric6DOFJoint3D::get_linear_motor_z_target_velocity);
	ClassDB::bind_method(D_METHOD("set_linear_motor_z_target_velocity", "value"), &PhantomGeneric6DOFJoint3D::set_linear_motor_z_target_velocity);
	ClassDB::bind_method(D_METHOD("get_linear_motor_z_max_force"), &PhantomGeneric6DOFJoint3D::get_linear_motor_z_max_force);
	ClassDB::bind_method(D_METHOD("set_linear_motor_z_max_force", "value"), &PhantomGeneric6DOFJoint3D::set_linear_motor_z_max_force);

	ClassDB::bind_method(D_METHOD("get_linear_spring_x_frequency"), &PhantomGeneric6DOFJoint3D::get_linear_spring_x_frequency);
	ClassDB::bind_method(D_METHOD("set_linear_spring_x_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_x_frequency);
	ClassDB::bind_method(D_METHOD("get_linear_spring_x_stiffness"), &PhantomGeneric6DOFJoint3D::get_linear_spring_x_stiffness);
	ClassDB::bind_method(D_METHOD("set_linear_spring_x_stiffness", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_x_stiffness);
	ClassDB::bind_method(D_METHOD("get_linear_spring_x_damping"), &PhantomGeneric6DOFJoint3D::get_linear_spring_x_damping);
	ClassDB::bind_method(D_METHOD("set_linear_spring_x_damping", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_x_damping);
	ClassDB::bind_method(D_METHOD("get_linear_spring_x_equilibrium_point"), &PhantomGeneric6DOFJoint3D::get_linear_spring_x_equilibrium_point);
	ClassDB::bind_method(D_METHOD("set_linear_spring_x_equilibrium_point", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_x_equilibrium_point);
	ClassDB::bind_method(D_METHOD("get_linear_spring_x_max_force"), &PhantomGeneric6DOFJoint3D::get_linear_spring_x_max_force);
	ClassDB::bind_method(D_METHOD("set_linear_spring_x_max_force", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_x_max_force);

	ClassDB::bind_method(D_METHOD("get_linear_spring_y_frequency"), &PhantomGeneric6DOFJoint3D::get_linear_spring_y_frequency);
	ClassDB::bind_method(D_METHOD("set_linear_spring_y_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_y_frequency);
	ClassDB::bind_method(D_METHOD("get_linear_spring_y_stiffness"), &PhantomGeneric6DOFJoint3D::get_linear_spring_y_stiffness);
	ClassDB::bind_method(D_METHOD("set_linear_spring_y_stiffness", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_y_stiffness);
	ClassDB::bind_method(D_METHOD("get_linear_spring_y_damping"), &PhantomGeneric6DOFJoint3D::get_linear_spring_y_damping);
	ClassDB::bind_method(D_METHOD("set_linear_spring_y_damping", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_y_damping);
	ClassDB::bind_method(D_METHOD("get_linear_spring_y_equilibrium_point"), &PhantomGeneric6DOFJoint3D::get_linear_spring_y_equilibrium_point);
	ClassDB::bind_method(D_METHOD("set_linear_spring_y_equilibrium_point", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_y_equilibrium_point);
	ClassDB::bind_method(D_METHOD("get_linear_spring_y_max_force"), &PhantomGeneric6DOFJoint3D::get_linear_spring_y_max_force);
	ClassDB::bind_method(D_METHOD("set_linear_spring_y_max_force", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_y_max_force);

	ClassDB::bind_method(D_METHOD("get_linear_spring_z_frequency"), &PhantomGeneric6DOFJoint3D::get_linear_spring_z_frequency);
	ClassDB::bind_method(D_METHOD("set_linear_spring_z_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_z_frequency);
	ClassDB::bind_method(D_METHOD("get_linear_spring_z_stiffness"), &PhantomGeneric6DOFJoint3D::get_linear_spring_z_stiffness);
	ClassDB::bind_method(D_METHOD("set_linear_spring_z_stiffness", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_z_stiffness);
	ClassDB::bind_method(D_METHOD("get_linear_spring_z_damping"), &PhantomGeneric6DOFJoint3D::get_linear_spring_z_damping);
	ClassDB::bind_method(D_METHOD("set_linear_spring_z_damping", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_z_damping);
	ClassDB::bind_method(D_METHOD("get_linear_spring_z_equilibrium_point"), &PhantomGeneric6DOFJoint3D::get_linear_spring_z_equilibrium_point);
	ClassDB::bind_method(D_METHOD("set_linear_spring_z_equilibrium_point", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_z_equilibrium_point);
	ClassDB::bind_method(D_METHOD("get_linear_spring_z_max_force"), &PhantomGeneric6DOFJoint3D::get_linear_spring_z_max_force);
	ClassDB::bind_method(D_METHOD("set_linear_spring_z_max_force", "value"), &PhantomGeneric6DOFJoint3D::set_linear_spring_z_max_force);

	ClassDB::bind_method(D_METHOD("get_linear_limit_x_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_limit_x_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_limit_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_limit_x_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_limit_y_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_limit_y_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_limit_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_limit_y_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_limit_z_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_limit_z_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_limit_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_limit_z_enabled);

	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_x_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_x_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_x_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_y_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_y_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_y_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_limit_spring_z_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_limit_spring_z_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_limit_spring_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_limit_spring_z_enabled);

	ClassDB::bind_method(D_METHOD("get_linear_motor_x_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_motor_x_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_motor_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_motor_x_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_motor_y_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_motor_y_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_motor_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_motor_y_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_motor_z_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_motor_z_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_motor_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_motor_z_enabled);

	ClassDB::bind_method(D_METHOD("get_linear_spring_x_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_spring_x_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_spring_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_spring_x_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_spring_y_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_spring_y_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_spring_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_spring_y_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_spring_z_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_spring_z_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_spring_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_spring_z_enabled);

	ClassDB::bind_method(D_METHOD("get_linear_spring_frequency_x_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_spring_frequency_x_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_spring_frequency_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_spring_frequency_x_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_spring_frequency_y_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_spring_frequency_y_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_spring_frequency_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_spring_frequency_y_enabled);
	ClassDB::bind_method(D_METHOD("get_linear_spring_frequency_z_enabled"), &PhantomGeneric6DOFJoint3D::get_linear_spring_frequency_z_enabled);
	ClassDB::bind_method(D_METHOD("set_linear_spring_frequency_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_linear_spring_frequency_z_enabled);

	ClassDB::bind_method(D_METHOD("get_angular_limit_x_upper"), &PhantomGeneric6DOFJoint3D::get_angular_limit_x_upper);
	ClassDB::bind_method(D_METHOD("set_angular_limit_x_upper", "value"), &PhantomGeneric6DOFJoint3D::set_angular_limit_x_upper);
	ClassDB::bind_method(D_METHOD("get_angular_limit_x_lower"), &PhantomGeneric6DOFJoint3D::get_angular_limit_x_lower);
	ClassDB::bind_method(D_METHOD("set_angular_limit_x_lower", "value"), &PhantomGeneric6DOFJoint3D::set_angular_limit_x_lower);

	ClassDB::bind_method(D_METHOD("get_angular_limit_y_upper"), &PhantomGeneric6DOFJoint3D::get_angular_limit_y_upper);
	ClassDB::bind_method(D_METHOD("set_angular_limit_y_upper", "value"), &PhantomGeneric6DOFJoint3D::set_angular_limit_y_upper);
	ClassDB::bind_method(D_METHOD("get_angular_limit_y_lower"), &PhantomGeneric6DOFJoint3D::get_angular_limit_y_lower);
	ClassDB::bind_method(D_METHOD("set_angular_limit_y_lower", "value"), &PhantomGeneric6DOFJoint3D::set_angular_limit_y_lower);

	ClassDB::bind_method(D_METHOD("get_angular_limit_z_upper"), &PhantomGeneric6DOFJoint3D::get_angular_limit_z_upper);
	ClassDB::bind_method(D_METHOD("set_angular_limit_z_upper", "value"), &PhantomGeneric6DOFJoint3D::set_angular_limit_z_upper);
	ClassDB::bind_method(D_METHOD("get_angular_limit_z_lower"), &PhantomGeneric6DOFJoint3D::get_angular_limit_z_lower);
	ClassDB::bind_method(D_METHOD("set_angular_limit_z_lower", "value"), &PhantomGeneric6DOFJoint3D::set_angular_limit_z_lower);

	ClassDB::bind_method(D_METHOD("get_angular_motor_x_target_velocity"), &PhantomGeneric6DOFJoint3D::get_angular_motor_x_target_velocity);
	ClassDB::bind_method(D_METHOD("set_angular_motor_x_target_velocity", "value"), &PhantomGeneric6DOFJoint3D::set_angular_motor_x_target_velocity);
	ClassDB::bind_method(D_METHOD("get_angular_motor_x_max_torque"), &PhantomGeneric6DOFJoint3D::get_angular_motor_x_max_torque);
	ClassDB::bind_method(D_METHOD("set_angular_motor_x_max_torque", "value"), &PhantomGeneric6DOFJoint3D::set_angular_motor_x_max_torque);

	ClassDB::bind_method(D_METHOD("get_angular_motor_y_target_velocity"), &PhantomGeneric6DOFJoint3D::get_angular_motor_y_target_velocity);
	ClassDB::bind_method(D_METHOD("set_angular_motor_y_target_velocity", "value"), &PhantomGeneric6DOFJoint3D::set_angular_motor_y_target_velocity);
	ClassDB::bind_method(D_METHOD("get_angular_motor_y_max_torque"), &PhantomGeneric6DOFJoint3D::get_angular_motor_y_max_torque);
	ClassDB::bind_method(D_METHOD("set_angular_motor_y_max_torque", "value"), &PhantomGeneric6DOFJoint3D::set_angular_motor_y_max_torque);

	ClassDB::bind_method(D_METHOD("get_angular_motor_z_target_velocity"), &PhantomGeneric6DOFJoint3D::get_angular_motor_z_target_velocity);
	ClassDB::bind_method(D_METHOD("set_angular_motor_z_target_velocity", "value"), &PhantomGeneric6DOFJoint3D::set_angular_motor_z_target_velocity);
	ClassDB::bind_method(D_METHOD("get_angular_motor_z_max_torque"), &PhantomGeneric6DOFJoint3D::get_angular_motor_z_max_torque);
	ClassDB::bind_method(D_METHOD("set_angular_motor_z_max_torque", "value"), &PhantomGeneric6DOFJoint3D::set_angular_motor_z_max_torque);

	ClassDB::bind_method(D_METHOD("get_angular_spring_x_frequency"), &PhantomGeneric6DOFJoint3D::get_angular_spring_x_frequency);
	ClassDB::bind_method(D_METHOD("set_angular_spring_x_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_x_frequency);
	ClassDB::bind_method(D_METHOD("get_angular_spring_x_stiffness"), &PhantomGeneric6DOFJoint3D::get_angular_spring_x_stiffness);
	ClassDB::bind_method(D_METHOD("set_angular_spring_x_stiffness", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_x_stiffness);
	ClassDB::bind_method(D_METHOD("get_angular_spring_x_damping"), &PhantomGeneric6DOFJoint3D::get_angular_spring_x_damping);
	ClassDB::bind_method(D_METHOD("set_angular_spring_x_damping", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_x_damping);
	ClassDB::bind_method(D_METHOD("get_angular_spring_x_equilibrium_point"), &PhantomGeneric6DOFJoint3D::get_angular_spring_x_equilibrium_point);
	ClassDB::bind_method(D_METHOD("set_angular_spring_x_equilibrium_point", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_x_equilibrium_point);
	ClassDB::bind_method(D_METHOD("get_angular_spring_x_max_torque"), &PhantomGeneric6DOFJoint3D::get_angular_spring_x_max_torque);
	ClassDB::bind_method(D_METHOD("set_angular_spring_x_max_torque", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_x_max_torque);

	ClassDB::bind_method(D_METHOD("get_angular_spring_y_frequency"), &PhantomGeneric6DOFJoint3D::get_angular_spring_y_frequency);
	ClassDB::bind_method(D_METHOD("set_angular_spring_y_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_y_frequency);
	ClassDB::bind_method(D_METHOD("get_angular_spring_y_stiffness"), &PhantomGeneric6DOFJoint3D::get_angular_spring_y_stiffness);
	ClassDB::bind_method(D_METHOD("set_angular_spring_y_stiffness", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_y_stiffness);
	ClassDB::bind_method(D_METHOD("get_angular_spring_y_damping"), &PhantomGeneric6DOFJoint3D::get_angular_spring_y_damping);
	ClassDB::bind_method(D_METHOD("set_angular_spring_y_damping", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_y_damping);
	ClassDB::bind_method(D_METHOD("get_angular_spring_y_equilibrium_point"), &PhantomGeneric6DOFJoint3D::get_angular_spring_y_equilibrium_point);
	ClassDB::bind_method(D_METHOD("set_angular_spring_y_equilibrium_point", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_y_equilibrium_point);
	ClassDB::bind_method(D_METHOD("get_angular_spring_y_max_torque"), &PhantomGeneric6DOFJoint3D::get_angular_spring_y_max_torque);
	ClassDB::bind_method(D_METHOD("set_angular_spring_y_max_torque", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_y_max_torque);

	ClassDB::bind_method(D_METHOD("get_angular_spring_z_frequency"), &PhantomGeneric6DOFJoint3D::get_angular_spring_z_frequency);
	ClassDB::bind_method(D_METHOD("set_angular_spring_z_frequency", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_z_frequency);
	ClassDB::bind_method(D_METHOD("get_angular_spring_z_stiffness"), &PhantomGeneric6DOFJoint3D::get_angular_spring_z_stiffness);
	ClassDB::bind_method(D_METHOD("set_angular_spring_z_stiffness", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_z_stiffness);
	ClassDB::bind_method(D_METHOD("get_angular_spring_z_damping"), &PhantomGeneric6DOFJoint3D::get_angular_spring_z_damping);
	ClassDB::bind_method(D_METHOD("set_angular_spring_z_damping", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_z_damping);
	ClassDB::bind_method(D_METHOD("get_angular_spring_z_equilibrium_point"), &PhantomGeneric6DOFJoint3D::get_angular_spring_z_equilibrium_point);
	ClassDB::bind_method(D_METHOD("set_angular_spring_z_equilibrium_point", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_z_equilibrium_point);
	ClassDB::bind_method(D_METHOD("get_angular_spring_z_max_torque"), &PhantomGeneric6DOFJoint3D::get_angular_spring_z_max_torque);
	ClassDB::bind_method(D_METHOD("set_angular_spring_z_max_torque", "value"), &PhantomGeneric6DOFJoint3D::set_angular_spring_z_max_torque);

	ClassDB::bind_method(D_METHOD("get_angular_limit_x_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_limit_x_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_limit_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_limit_x_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_limit_y_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_limit_y_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_limit_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_limit_y_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_limit_z_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_limit_z_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_limit_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_limit_z_enabled);

	ClassDB::bind_method(D_METHOD("get_angular_motor_x_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_motor_x_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_motor_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_motor_x_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_motor_y_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_motor_y_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_motor_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_motor_y_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_motor_z_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_motor_z_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_motor_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_motor_z_enabled);

	ClassDB::bind_method(D_METHOD("get_angular_spring_x_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_spring_x_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_spring_x_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_spring_x_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_spring_y_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_spring_y_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_spring_y_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_spring_y_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_spring_z_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_spring_z_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_spring_z_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_spring_z_enabled);

	ClassDB::bind_method(D_METHOD("get_angular_spring_x_frequency_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_spring_x_frequency_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_spring_x_frequency_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_spring_x_frequency_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_spring_y_frequency_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_spring_y_frequency_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_spring_y_frequency_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_spring_y_frequency_enabled);
	ClassDB::bind_method(D_METHOD("get_angular_spring_z_frequency_enabled"), &PhantomGeneric6DOFJoint3D::get_angular_spring_z_frequency_enabled);
	ClassDB::bind_method(D_METHOD("set_angular_spring_z_frequency_enabled", "enabled"), &PhantomGeneric6DOFJoint3D::set_angular_spring_z_frequency_enabled);

	ClassDB::bind_method(D_METHOD("get_applied_force"), &PhantomGeneric6DOFJoint3D::get_applied_force);
	ClassDB::bind_method(D_METHOD("get_applied_torque"), &PhantomGeneric6DOFJoint3D::get_applied_torque);

	ClassDB::bind_method(D_METHOD("set_target_rotation", "rotation"), &PhantomGeneric6DOFJoint3D::set_target_rotation);

	ADD_GROUP("Linear Limit", "linear_limit_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_limit_x_enabled"), "set_linear_limit_x_enabled", "get_linear_limit_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_x_upper", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_limit_x_upper", "get_linear_limit_x_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_x_lower", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_limit_x_lower", "get_linear_limit_x_lower");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_limit_y_enabled"), "set_linear_limit_y_enabled", "get_linear_limit_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_y_upper", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_limit_y_upper", "get_linear_limit_y_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_y_lower", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_limit_y_lower", "get_linear_limit_y_lower");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_limit_z_enabled"), "set_linear_limit_z_enabled", "get_linear_limit_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_z_upper", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_limit_z_upper", "get_linear_limit_z_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_z_lower", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_limit_z_lower", "get_linear_limit_z_lower");

	ADD_GROUP("Linear Limit Spring", "linear_limit_spring_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_limit_spring_x_enabled"), "set_linear_limit_spring_x_enabled", "get_linear_limit_spring_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_spring_x_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_linear_limit_spring_x_frequency", "get_linear_limit_spring_x_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_spring_x_damping"), "set_linear_limit_spring_x_damping", "get_linear_limit_spring_x_damping");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_limit_spring_y_enabled"), "set_linear_limit_spring_y_enabled", "get_linear_limit_spring_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_spring_y_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_linear_limit_spring_y_frequency", "get_linear_limit_spring_y_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_spring_y_damping"), "set_linear_limit_spring_y_damping", "get_linear_limit_spring_y_damping");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_limit_spring_z_enabled"), "set_linear_limit_spring_z_enabled", "get_linear_limit_spring_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_spring_z_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_linear_limit_spring_z_frequency", "get_linear_limit_spring_z_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_limit_spring_z_damping"), "set_linear_limit_spring_z_damping", "get_linear_limit_spring_z_damping");

	ADD_GROUP("Linear Motor", "linear_motor_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_motor_x_enabled"), "set_linear_motor_x_enabled", "get_linear_motor_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_motor_x_target_velocity", PROPERTY_HINT_NONE, "suffix:m/s"), "set_linear_motor_x_target_velocity", "get_linear_motor_x_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_motor_x_max_force", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m/s\u00B2 (N)"), "set_linear_motor_x_max_force", "get_linear_motor_x_max_force");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_motor_y_enabled"), "set_linear_motor_y_enabled", "get_linear_motor_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_motor_y_target_velocity", PROPERTY_HINT_NONE, "suffix:m/s"), "set_linear_motor_y_target_velocity", "get_linear_motor_y_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_motor_y_max_force", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m/s\u00B2 (N)"), "set_linear_motor_y_max_force", "get_linear_motor_y_max_force");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_motor_z_enabled"), "set_linear_motor_z_enabled", "get_linear_motor_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_motor_z_target_velocity", PROPERTY_HINT_NONE, "suffix:m/s"), "set_linear_motor_z_target_velocity", "get_linear_motor_z_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_motor_z_max_force", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m/s\u00B2 (N)"), "set_linear_motor_z_max_force", "get_linear_motor_z_max_force");

	ADD_GROUP("Linear Spring", "linear_spring_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_spring_x_enabled"), "set_linear_spring_x_enabled", "get_linear_spring_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_spring_frequency_x_enabled"), "set_linear_spring_frequency_x_enabled", "get_linear_spring_frequency_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_x_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_linear_spring_x_frequency", "get_linear_spring_x_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_x_stiffness", PROPERTY_HINT_NONE, ""), "set_linear_spring_x_stiffness", "get_linear_spring_x_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_x_damping"), "set_linear_spring_x_damping", "get_linear_spring_x_damping");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_x_equilibrium_point", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_spring_x_equilibrium_point", "get_linear_spring_x_equilibrium_point");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_x_max_force", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m/s\u00B2 (N)"), "set_linear_spring_x_max_force", "get_linear_spring_x_max_force");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_spring_y_enabled"), "set_linear_spring_y_enabled", "get_linear_spring_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_spring_frequency_y_enabled"), "set_linear_spring_frequency_y_enabled", "get_linear_spring_frequency_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_y_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_linear_spring_y_frequency", "get_linear_spring_y_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_y_stiffness", PROPERTY_HINT_NONE, ""), "set_linear_spring_y_stiffness", "get_linear_spring_y_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_y_damping"), "set_linear_spring_y_damping", "get_linear_spring_y_damping");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_y_equilibrium_point", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_spring_y_equilibrium_point", "get_linear_spring_y_equilibrium_point");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_y_max_force", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m/s\u00B2 (N)"), "set_linear_spring_y_max_force", "get_linear_spring_y_max_force");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_spring_z_enabled"), "set_linear_spring_z_enabled", "get_linear_spring_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "linear_spring_frequency_z_enabled"), "set_linear_spring_frequency_z_enabled", "get_linear_spring_frequency_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_z_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_linear_spring_z_frequency", "get_linear_spring_z_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_z_stiffness", PROPERTY_HINT_NONE, ""), "set_linear_spring_z_stiffness", "get_linear_spring_z_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_z_damping"), "set_linear_spring_z_damping", "get_linear_spring_z_damping");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_z_equilibrium_point", PROPERTY_HINT_NONE, "suffix:m"), "set_linear_spring_z_equilibrium_point", "get_linear_spring_z_equilibrium_point");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "linear_spring_z_max_force", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m/s\u00B2 (N)"), "set_linear_spring_z_max_force", "get_linear_spring_z_max_force");

	ADD_GROUP("Angular Limit", "angular_limit_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_limit_x_enabled"), "set_angular_limit_x_enabled", "get_angular_limit_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_limit_x_upper", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_limit_x_upper", "get_angular_limit_x_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_limit_x_lower", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_limit_x_lower", "get_angular_limit_x_lower");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_limit_y_enabled"), "set_angular_limit_y_enabled", "get_angular_limit_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_limit_y_upper", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_limit_y_upper", "get_angular_limit_y_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_limit_y_lower", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_limit_y_lower", "get_angular_limit_y_lower");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_limit_z_enabled"), "set_angular_limit_z_enabled", "get_angular_limit_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_limit_z_upper", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_limit_z_upper", "get_angular_limit_z_upper");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_limit_z_lower", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_limit_z_lower", "get_angular_limit_z_lower");

	ADD_GROUP("Angular Motor", "angular_motor_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_motor_x_enabled"), "set_angular_motor_x_enabled", "get_angular_motor_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_motor_x_target_velocity", PROPERTY_HINT_NONE, U"radians_as_degrees,suffix:°/s"), "set_angular_motor_x_target_velocity", "get_angular_motor_x_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_motor_x_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_angular_motor_x_max_torque", "get_angular_motor_x_max_torque");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_motor_y_enabled"), "set_angular_motor_y_enabled", "get_angular_motor_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_motor_y_target_velocity", PROPERTY_HINT_NONE, U"radians_as_degrees,suffix:°/s"), "set_angular_motor_y_target_velocity", "get_angular_motor_y_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_motor_y_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_angular_motor_y_max_torque", "get_angular_motor_y_max_torque");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_motor_z_enabled"), "set_angular_motor_z_enabled", "get_angular_motor_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_motor_z_target_velocity", PROPERTY_HINT_NONE, U"radians_as_degrees,suffix:°/s"), "set_angular_motor_z_target_velocity", "get_angular_motor_z_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_motor_z_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_angular_motor_z_max_torque", "get_angular_motor_z_max_torque");

	ADD_GROUP("Angular Spring", "angular_spring_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_spring_x_enabled"), "set_angular_spring_x_enabled", "get_angular_spring_x_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_spring_x_frequency_enabled"), "set_angular_spring_x_frequency_enabled", "get_angular_spring_x_frequency_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_x_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_angular_spring_x_frequency", "get_angular_spring_x_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_x_stiffness", PROPERTY_HINT_NONE, ""), "set_angular_spring_x_stiffness", "get_angular_spring_x_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_x_damping"), "set_angular_spring_x_damping", "get_angular_spring_x_damping");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_x_equilibrium_point", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_spring_x_equilibrium_point", "get_angular_spring_x_equilibrium_point");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_x_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_angular_spring_x_max_torque", "get_angular_spring_x_max_torque");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_spring_y_enabled"), "set_angular_spring_y_enabled", "get_angular_spring_y_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_spring_y_frequency_enabled"), "set_angular_spring_y_frequency_enabled", "get_angular_spring_y_frequency_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_y_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_angular_spring_y_frequency", "get_angular_spring_y_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_y_stiffness", PROPERTY_HINT_NONE, ""), "set_angular_spring_y_stiffness", "get_angular_spring_y_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_y_damping"), "set_angular_spring_y_damping", "get_angular_spring_y_damping");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_y_equilibrium_point", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_spring_y_equilibrium_point", "get_angular_spring_y_equilibrium_point");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_y_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_angular_spring_y_max_torque", "get_angular_spring_y_max_torque");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_spring_z_enabled"), "set_angular_spring_z_enabled", "get_angular_spring_z_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "angular_spring_z_frequency_enabled"), "set_angular_spring_z_frequency_enabled", "get_angular_spring_z_frequency_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_z_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_angular_spring_z_frequency", "get_angular_spring_z_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_z_stiffness", PROPERTY_HINT_NONE, ""), "set_angular_spring_z_stiffness", "get_angular_spring_z_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_z_damping"), "set_angular_spring_z_damping", "get_angular_spring_z_damping");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_z_equilibrium_point", PROPERTY_HINT_NONE, "radians_as_degrees"), "set_angular_spring_z_equilibrium_point", "get_angular_spring_z_equilibrium_point");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "angular_spring_z_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_angular_spring_z_max_torque", "get_angular_spring_z_max_torque");

	BIND_ENUM_CONSTANT(PARAM_LINEAR_LIMIT_UPPER);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_LIMIT_LOWER);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_LIMIT_SPRING_FREQUENCY);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_LIMIT_SPRING_DAMPING);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_MOTOR_TARGET_VELOCITY);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_MOTOR_MAX_FORCE);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_SPRING_FREQUENCY);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_SPRING_STIFFNESS);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_SPRING_DAMPING);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_SPRING_EQUILIBRIUM_POINT);
	BIND_ENUM_CONSTANT(PARAM_LINEAR_SPRING_MAX_FORCE);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_LIMIT_UPPER);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_LIMIT_LOWER);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_MOTOR_TARGET_VELOCITY);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_MOTOR_MAX_TORQUE);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_SPRING_FREQUENCY);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_SPRING_STIFFNESS);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_SPRING_DAMPING);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_SPRING_EQUILIBRIUM_POINT);
	BIND_ENUM_CONSTANT(PARAM_ANGULAR_SPRING_MAX_TORQUE);

	BIND_ENUM_CONSTANT(FLAG_ENABLE_LINEAR_LIMIT);
	BIND_ENUM_CONSTANT(FLAG_ENABLE_LINEAR_LIMIT_SPRING);
	BIND_ENUM_CONSTANT(FLAG_ENABLE_LINEAR_MOTOR);
	BIND_ENUM_CONSTANT(FLAG_ENABLE_LINEAR_SPRING);
	BIND_ENUM_CONSTANT(FLAG_ENABLE_ANGULAR_LIMIT);
	BIND_ENUM_CONSTANT(FLAG_ENABLE_ANGULAR_MOTOR);
	BIND_ENUM_CONSTANT(FLAG_ENABLE_ANGULAR_SPRING);

	BIND_ENUM_CONSTANT(FLAG_ENABLE_LINEAR_SPRING_FREQUENCY);
	BIND_ENUM_CONSTANT(FLAG_ENABLE_ANGULAR_SPRING_FREQUENCY);
}

PhantomGeneric6DOFJoint3D::PhantomGeneric6DOFJoint3D() {
	std::fill_n(linear_limit_spring_frequency, AXIS_COUNT, 0.0);
	std::fill_n(linear_limit_spring_damping, AXIS_COUNT, 0.0);
	std::fill_n(linear_motor_max_force, AXIS_COUNT, INFINITY);
	std::fill_n(linear_spring_frequency, AXIS_COUNT, 0.0);
	std::fill_n(linear_spring_damping, AXIS_COUNT, 0.0);
	std::fill_n(linear_spring_max_force, AXIS_COUNT, INFINITY);
	std::fill_n(angular_motor_max_torque, AXIS_COUNT, INFINITY);
	std::fill_n(angular_spring_frequency, AXIS_COUNT, 0.0);
	std::fill_n(angular_spring_damping, AXIS_COUNT, 0.0);
	std::fill_n(angular_spring_max_torque, AXIS_COUNT, INFINITY);
	std::fill_n(linear_limit_enabled, AXIS_COUNT, true);
	std::fill_n(angular_limit_enabled, AXIS_COUNT, true);
}

double PhantomGeneric6DOFJoint3D::get_param(Axis p_axis, Param p_param) const {
	const double *value = _get_param_ptr(p_axis, p_param);
	if (unlikely(value == nullptr)) {
		return 0.0;
	}

	return *value;
}

void PhantomGeneric6DOFJoint3D::set_param(Axis p_axis, Param p_param, double p_value) {
	double *value = _get_param_ptr(p_axis, p_param);
	if (unlikely(value == nullptr)) {
		return;
	}

	if (*value == p_value) {
		return;
	}

	*value = p_value;

	_param_changed(p_axis, p_param);
}

bool PhantomGeneric6DOFJoint3D::get_flag(Axis p_axis, Flag p_flag) const {
	const bool *value = _get_flag_ptr(p_axis, p_flag);
	if (unlikely(value == nullptr)) {
		return false;
	}

	return *value;
}

void PhantomGeneric6DOFJoint3D::set_flag(Axis p_axis, Flag p_flag, bool p_enabled) {
	bool *value = _get_flag_ptr(p_axis, p_flag);
	if (unlikely(value == nullptr)) {
		return;
	}

	if (*value == p_enabled) {
		return;
	}

	*value = p_enabled;

	_flag_changed(p_axis, p_flag);
}

float PhantomGeneric6DOFJoint3D::get_applied_force() const {
	JoltPhysicsServer3D *server = _get_jolt_physics_server();
	if (unlikely(server == nullptr)) {
		return 0.0f;
	}

	return server->generic_6dof_joint_get_applied_force(rid);
}

float PhantomGeneric6DOFJoint3D::get_applied_torque() const {
	JoltPhysicsServer3D *server = _get_jolt_physics_server();
	if (unlikely(server == nullptr)) {
		return 0.0f;
	}

	return server->generic_6dof_joint_get_applied_torque(rid);
}

void PhantomGeneric6DOFJoint3D::set_target_rotation(Basis p_rotation) {
	JoltPhysicsServer3D *server = _get_jolt_physics_server();
	if (unlikely(server == nullptr)) {
		return;
	}

	server->generic_6dof_joint_set_target_rotation(rid, p_rotation);
}

void PhantomGeneric6DOFJoint3D::_configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) {
	PhysicsServer3D *server = _get_physics_server();
	ERR_FAIL_NULL(server);

	server->joint_make_generic_6dof(
			rid,
			p_body_a->get_rid(),
			_get_body_local_transform(*p_body_a),
			p_body_b != nullptr ? p_body_b->get_rid() : RID(),
			p_body_b != nullptr ? _get_body_local_transform(*p_body_b) : get_global_transform().orthonormalized());

	for (int32_t i = 0; i < AXIS_COUNT; ++i) {
		const auto axis = (Axis)i;

		_update_param(axis, PARAM_LINEAR_LIMIT_UPPER);
		_update_param(axis, PARAM_LINEAR_LIMIT_LOWER);
		_update_param(axis, PARAM_LINEAR_MOTOR_TARGET_VELOCITY);
		_update_param(axis, PARAM_LINEAR_MOTOR_MAX_FORCE);
		_update_param(axis, PARAM_LINEAR_SPRING_STIFFNESS);
		_update_param(axis, PARAM_LINEAR_SPRING_DAMPING);
		_update_param(axis, PARAM_LINEAR_SPRING_EQUILIBRIUM_POINT);
		_update_param(axis, PARAM_ANGULAR_LIMIT_UPPER);
		_update_param(axis, PARAM_ANGULAR_LIMIT_LOWER);
		_update_param(axis, PARAM_ANGULAR_MOTOR_TARGET_VELOCITY);
		_update_param(axis, PARAM_ANGULAR_MOTOR_MAX_TORQUE);
		_update_param(axis, PARAM_ANGULAR_SPRING_STIFFNESS);
		_update_param(axis, PARAM_ANGULAR_SPRING_DAMPING);
		_update_param(axis, PARAM_ANGULAR_SPRING_EQUILIBRIUM_POINT);

		_update_jolt_param(axis, PARAM_LINEAR_LIMIT_SPRING_FREQUENCY);
		_update_jolt_param(axis, PARAM_LINEAR_LIMIT_SPRING_DAMPING);
		_update_jolt_param(axis, PARAM_LINEAR_SPRING_FREQUENCY);
		_update_jolt_param(axis, PARAM_LINEAR_SPRING_MAX_FORCE);
		_update_jolt_param(axis, PARAM_ANGULAR_SPRING_FREQUENCY);
		_update_jolt_param(axis, PARAM_ANGULAR_SPRING_MAX_TORQUE);

		_update_flag(axis, FLAG_ENABLE_LINEAR_LIMIT);
		_update_flag(axis, FLAG_ENABLE_LINEAR_MOTOR);
		_update_flag(axis, FLAG_ENABLE_LINEAR_SPRING);
		_update_flag(axis, FLAG_ENABLE_ANGULAR_LIMIT);
		_update_flag(axis, FLAG_ENABLE_ANGULAR_MOTOR);
		_update_flag(axis, FLAG_ENABLE_ANGULAR_SPRING);

		_update_jolt_flag(axis, FLAG_ENABLE_LINEAR_LIMIT_SPRING);
		_update_jolt_flag(axis, FLAG_ENABLE_LINEAR_SPRING_FREQUENCY);
		_update_jolt_flag(axis, FLAG_ENABLE_ANGULAR_SPRING_FREQUENCY);
	}
}

const double *PhantomGeneric6DOFJoint3D::_get_param_ptr(Axis p_axis, Param p_param) const {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
	return const_cast<PhantomGeneric6DOFJoint3D *>(this)->_get_param_ptr(p_axis, p_param);
}

double *PhantomGeneric6DOFJoint3D::_get_param_ptr(Axis p_axis, Param p_param) {
	switch (p_param) {
		case PARAM_LINEAR_LIMIT_UPPER: {
			return &linear_limit_upper[p_axis];
		}
		case PARAM_LINEAR_LIMIT_LOWER: {
			return &linear_limit_lower[p_axis];
		}
		case PARAM_LINEAR_LIMIT_SPRING_FREQUENCY: {
			return &linear_limit_spring_frequency[p_axis];
		}
		case PARAM_LINEAR_LIMIT_SPRING_DAMPING: {
			return &linear_limit_spring_damping[p_axis];
		}
		case PARAM_LINEAR_MOTOR_TARGET_VELOCITY: {
			return &linear_motor_target_velocity[p_axis];
		}
		case PARAM_LINEAR_MOTOR_MAX_FORCE: {
			return &linear_motor_max_force[p_axis];
		}
		case PARAM_LINEAR_SPRING_FREQUENCY: {
			return &linear_spring_frequency[p_axis];
		}
		case PARAM_LINEAR_SPRING_STIFFNESS: {
			return &linear_spring_frequency[p_axis];
		}
		case PARAM_LINEAR_SPRING_DAMPING: {
			return &linear_spring_damping[p_axis];
		}
		case PARAM_LINEAR_SPRING_EQUILIBRIUM_POINT: {
			return &linear_spring_equilibrium_point[p_axis];
		}
		case PARAM_LINEAR_SPRING_MAX_FORCE: {
			return &linear_spring_max_force[p_axis];
		}
		case PARAM_ANGULAR_LIMIT_UPPER: {
			return &angular_limit_upper[p_axis];
		}
		case PARAM_ANGULAR_LIMIT_LOWER: {
			return &angular_limit_lower[p_axis];
		}
		case PARAM_ANGULAR_MOTOR_TARGET_VELOCITY: {
			return &angular_motor_target_velocity[p_axis];
		}
		case PARAM_ANGULAR_MOTOR_MAX_TORQUE: {
			return &angular_motor_max_torque[p_axis];
		}
		case PARAM_ANGULAR_SPRING_FREQUENCY: {
			return &angular_spring_frequency[p_axis];
		}
		case PARAM_ANGULAR_SPRING_STIFFNESS: {
			return &angular_spring_stiffness[p_axis];
		}
		case PARAM_ANGULAR_SPRING_DAMPING: {
			return &angular_spring_damping[p_axis];
		}
		case PARAM_ANGULAR_SPRING_EQUILIBRIUM_POINT: {
			return &angular_spring_equilibrium_point[p_axis];
		}
		case PARAM_ANGULAR_SPRING_MAX_TORQUE: {
			return &angular_spring_max_torque[p_axis];
		}
		default: {
			ERR_FAIL_V_MSG(nullptr, vformat("Unhandled parameter: '%d'.", p_param));
		}
	}
}

const bool *PhantomGeneric6DOFJoint3D::_get_flag_ptr(Axis p_axis, Flag p_flag) const {
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
	return const_cast<PhantomGeneric6DOFJoint3D *>(this)->_get_flag_ptr(p_axis, p_flag);
}

bool *PhantomGeneric6DOFJoint3D::_get_flag_ptr(Axis p_axis, Flag p_flag) {
	switch (p_flag) {
		case FLAG_ENABLE_LINEAR_LIMIT: {
			return &linear_limit_enabled[p_axis];
		}
		case FLAG_ENABLE_LINEAR_LIMIT_SPRING: {
			return &linear_limit_spring_enabled[p_axis];
		}
		case FLAG_ENABLE_LINEAR_MOTOR: {
			return &linear_motor_enabled[p_axis];
		}
		case FLAG_ENABLE_LINEAR_SPRING: {
			return &linear_spring_enabled[p_axis];
		}
		case FLAG_ENABLE_LINEAR_SPRING_FREQUENCY: {
			return &linear_spring_frequency_enabled[p_axis];
		}
		case FLAG_ENABLE_ANGULAR_LIMIT: {
			return &angular_limit_enabled[p_axis];
		}
		case FLAG_ENABLE_ANGULAR_MOTOR: {
			return &angular_motor_enabled[p_axis];
		}
		case FLAG_ENABLE_ANGULAR_SPRING: {
			return &angular_spring_enabled[p_axis];
		}
		case FLAG_ENABLE_ANGULAR_SPRING_FREQUENCY: {
			return &angular_spring_frequency_enabled[p_axis];
		}
		default: {
			ERR_FAIL_V_MSG(nullptr, vformat("Unhandled flag: '%d'.", p_flag));
		}
	}
}

void PhantomGeneric6DOFJoint3D::_update_param(Axis p_axis, Param p_param, double p_value) {
	if (unlikely(_is_invalid())) {
		return;
	}

	PhysicsServer3D *server = _get_physics_server();
	if (unlikely(server == nullptr)) {
		return;
	}

	server->generic_6dof_joint_set_param(rid, p_axis, (ServerParam)p_param, (real_t)p_value);
}

void PhantomGeneric6DOFJoint3D::_update_param(Axis p_axis, Param p_param) {
	const double *value = _get_param_ptr(p_axis, p_param);
	ERR_FAIL_NULL(value);

	_update_param(p_axis, p_param, *value);
}

void PhantomGeneric6DOFJoint3D::_update_jolt_param(Axis p_axis, Param p_param, double p_value) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *server = _get_jolt_physics_server();
	if (unlikely(server == nullptr)) {
		return;
	}

	server->generic_6dof_joint_set_jolt_param(rid, p_axis, (ServerParamJolt)p_param, p_value);
}

void PhantomGeneric6DOFJoint3D::_update_jolt_param(Axis p_axis, Param p_param) {
	const double *value = _get_param_ptr(p_axis, p_param);
	ERR_FAIL_NULL(value);

	_update_jolt_param(p_axis, p_param, *value);
}

void PhantomGeneric6DOFJoint3D::_update_flag(Axis p_axis, Flag p_flag, bool p_enabled) {
	if (unlikely(_is_invalid())) {
		return;
	}

	PhysicsServer3D *server = _get_physics_server();
	if (unlikely(server == nullptr)) {
		return;
	}

	server->generic_6dof_joint_set_flag(rid, p_axis, (ServerFlag)p_flag, p_enabled);
}

void PhantomGeneric6DOFJoint3D::_update_flag(Axis p_axis, Flag p_flag) {
	const bool *value = _get_flag_ptr(p_axis, p_flag);
	ERR_FAIL_NULL(value);

	_update_flag(p_axis, p_flag, *value);
}

void PhantomGeneric6DOFJoint3D::_update_jolt_flag(Axis p_axis, Flag p_flag, bool p_enabled) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *server = _get_jolt_physics_server();
	if (unlikely(server == nullptr)) {
		return;
	}

	server->generic_6dof_joint_set_jolt_flag(rid, p_axis, (ServerFlagJolt)p_flag, p_enabled);
}

void PhantomGeneric6DOFJoint3D::_update_jolt_flag(Axis p_axis, Flag p_flag) {
	const bool *value = _get_flag_ptr(p_axis, p_flag);
	if (unlikely(value == nullptr)) {
		return;
	}

	_update_jolt_flag(p_axis, p_flag, *value);
}

void PhantomGeneric6DOFJoint3D::_param_changed(Axis p_axis, Param p_param) {
	switch (p_param) {
		case PARAM_LINEAR_LIMIT_UPPER:
		case PARAM_LINEAR_LIMIT_LOWER:
		case PARAM_LINEAR_MOTOR_TARGET_VELOCITY:
		case PARAM_LINEAR_MOTOR_MAX_FORCE:
		case PARAM_LINEAR_SPRING_STIFFNESS:
		case PARAM_LINEAR_SPRING_DAMPING:
		case PARAM_LINEAR_SPRING_EQUILIBRIUM_POINT:
		case PARAM_ANGULAR_LIMIT_UPPER:
		case PARAM_ANGULAR_LIMIT_LOWER:
		case PARAM_ANGULAR_MOTOR_TARGET_VELOCITY:
		case PARAM_ANGULAR_MOTOR_MAX_TORQUE:
		case PARAM_ANGULAR_SPRING_STIFFNESS:
		case PARAM_ANGULAR_SPRING_DAMPING:
		case PARAM_ANGULAR_SPRING_EQUILIBRIUM_POINT: {
			_update_param(p_axis, p_param);
		} break;

		case PARAM_LINEAR_LIMIT_SPRING_FREQUENCY:
		case PARAM_LINEAR_LIMIT_SPRING_DAMPING:
		case PARAM_LINEAR_SPRING_FREQUENCY:

		case PARAM_LINEAR_SPRING_MAX_FORCE:
		case PARAM_ANGULAR_SPRING_FREQUENCY:
		case PARAM_ANGULAR_SPRING_MAX_TORQUE: {
			_update_jolt_param(p_axis, p_param);
		} break;

		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}
}

void PhantomGeneric6DOFJoint3D::_flag_changed(Axis p_axis, Flag p_flag) {
	switch (p_flag) {
		case FLAG_ENABLE_LINEAR_LIMIT:
		case FLAG_ENABLE_LINEAR_MOTOR:
		case FLAG_ENABLE_LINEAR_SPRING:
		case FLAG_ENABLE_ANGULAR_LIMIT:
		case FLAG_ENABLE_ANGULAR_MOTOR:
		case FLAG_ENABLE_ANGULAR_SPRING: {
			_update_flag(p_axis, p_flag);
		} break;

		case FLAG_ENABLE_LINEAR_LIMIT_SPRING:
		case FLAG_ENABLE_LINEAR_SPRING_FREQUENCY:
		case FLAG_ENABLE_ANGULAR_SPRING_FREQUENCY: {
			_update_jolt_flag(p_axis, p_flag);
		} break;

		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}
}
