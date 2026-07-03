#pragma once

#include "phantom_joint_3d.h"
#include "scene/3d/physics/physics_body_3d.h"

class PhantomPinJoint3D final : public PhantomJoint3D {
	GDCLASS(PhantomPinJoint3D, PhantomJoint3D)

protected:
	static void _bind_methods();

public:
	float get_applied_force() const;

private:
	void _configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) override;
};
