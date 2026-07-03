#include "phantom_pin_joint_3d.h"

#include "../jolt_physics_server_3d.h"
#include "core/object/class_db.h"

void PhantomPinJoint3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_applied_force"), &PhantomPinJoint3D::get_applied_force);
}

float PhantomPinJoint3D::get_applied_force() const {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return 0.0f;
	}

	return physics_server->pin_joint_get_applied_force(rid);
}

void PhantomPinJoint3D::_configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	const Vector3 global_position = get_global_position();

	physics_server->joint_make_pin(
			rid,
			p_body_a->get_rid(),
			p_body_a->to_local(global_position),
			p_body_b != nullptr ? p_body_b->get_rid() : RID(),
			p_body_b != nullptr ? p_body_b->to_local(global_position) : global_position);
}
