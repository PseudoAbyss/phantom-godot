#include "phantom_joint_3d.h"

#include "../jolt_physics_server_3d.h"

#include "core/object/callable_mp.h"
#include "core/object/class_db.h"

void PhantomJoint3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_enabled"), &PhantomJoint3D::get_enabled);
	ClassDB::bind_method(D_METHOD("set_enabled", "enabled"), &PhantomJoint3D::set_enabled);

	ClassDB::bind_method(D_METHOD("get_node_a"), &PhantomJoint3D::get_node_a);
	ClassDB::bind_method(D_METHOD("set_node_a", "path"), &PhantomJoint3D::set_node_a);

	ClassDB::bind_method(D_METHOD("get_node_b"), &PhantomJoint3D::get_node_b);
	ClassDB::bind_method(D_METHOD("set_node_b", "path"), &PhantomJoint3D::set_node_b);

	ClassDB::bind_method(D_METHOD("get_exclude_nodes_from_collision"), &PhantomJoint3D::get_exclude_nodes_from_collision);
	ClassDB::bind_method(D_METHOD("set_exclude_nodes_from_collision", "excluded"), &PhantomJoint3D::set_exclude_nodes_from_collision);

	ClassDB::bind_method(D_METHOD("get_solver_priority"), &PhantomJoint3D::get_solver_priority);
	ClassDB::bind_method(D_METHOD("set_solver_priority", "priority"), &PhantomJoint3D::set_solver_priority);

	ClassDB::bind_method(D_METHOD("get_solver_velocity_iterations"), &PhantomJoint3D::get_solver_velocity_iterations);
	ClassDB::bind_method(D_METHOD("set_solver_velocity_iterations", "iterations"), &PhantomJoint3D::set_solver_velocity_iterations);

	ClassDB::bind_method(D_METHOD("get_solver_position_iterations"), &PhantomJoint3D::get_solver_position_iterations);
	ClassDB::bind_method(D_METHOD("set_solver_position_iterations", "iterations"), &PhantomJoint3D::set_solver_position_iterations);

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "node_a", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "PhysicsBody3D"), "set_node_a", "get_node_a");
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "node_b", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "PhysicsBody3D"), "set_node_b", "get_node_b");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enabled"), "set_enabled", "get_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "exclude_nodes_from_collision"), "set_exclude_nodes_from_collision", "get_exclude_nodes_from_collision");

	ADD_GROUP("Solver Overrides", "solver_");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "solver_priority", PROPERTY_HINT_RANGE, "0,64,or_greater"), "set_solver_priority", "get_solver_priority");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "solver_velocity_iterations", PROPERTY_HINT_RANGE, "0,64,or_greater"), "set_solver_velocity_iterations", "get_solver_velocity_iterations");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "solver_position_iterations", PROPERTY_HINT_RANGE, "0,64,or_greater"), "set_solver_position_iterations", "get_solver_position_iterations");
}

PhantomJoint3D::PhantomJoint3D() {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	rid = physics_server->joint_create();
}

PhantomJoint3D::~PhantomJoint3D() {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->free_rid(rid);
}

void PhantomJoint3D::set_node_a(const NodePath &p_path) {
	// NOTE(mihe): We can't do a dirty check on the node path here, because when renaming nodes it
	// ends up calling the setter twice, and the node path won't be valid the first time around.

	_nodes_changing();
	node_a = p_path;
	_nodes_changed();
}

void PhantomJoint3D::set_node_b(const NodePath &p_path) {
	// NOTE(mihe): We can't do a dirty check on the node path here, because when renaming nodes it
	// ends up calling the setter twice, and the node path won't be valid the first time around.

	_nodes_changing();
	node_b = p_path;
	_nodes_changed();
}

PhysicsBody3D *PhantomJoint3D::get_body_a() const {
	if (unlikely(!is_inside_tree())) {
		return nullptr;
	}
	return Object::cast_to<PhysicsBody3D>(get_node_or_null(node_a));
}

PhysicsBody3D *PhantomJoint3D::get_body_b() const {
	if (unlikely(!is_inside_tree())) {
		return nullptr;
	}
	return Object::cast_to<PhysicsBody3D>(get_node_or_null(node_b));
}

void PhantomJoint3D::set_enabled(bool p_enabled) {
	if (enabled == p_enabled) {
		return;
	}

	enabled = p_enabled;

	_enabled_changed();
}

void PhantomJoint3D::set_exclude_nodes_from_collision(bool p_excluded) {
	if (collision_excluded == p_excluded) {
		return;
	}

	collision_excluded = p_excluded;

	_collision_exclusion_changed();
}

void PhantomJoint3D::set_solver_priority(int32_t p_solver_priority) {
	if (solver_priority == p_solver_priority) {
		return;
	}

	solver_priority = p_solver_priority;

	_solver_priority_changed();
}

void PhantomJoint3D::set_solver_velocity_iterations(int32_t p_iterations) {
	if (velocity_iterations == p_iterations) {
		return;
	}

	velocity_iterations = p_iterations;

	_velocity_iterations_changed();
}

void PhantomJoint3D::set_solver_position_iterations(int32_t p_iterations) {
	if (position_iterations == p_iterations) {
		return;
	}

	position_iterations = p_iterations;

	_position_iterations_changed();
}

PackedStringArray PhantomJoint3D::get_configuration_warnings() const {
	PackedStringArray warnings = Node3D::get_configuration_warnings();

	if (!warning.is_empty()) {
		warnings.push_back(warning);
	}

	return warnings;
}

PhysicsServer3D *PhantomJoint3D::_get_physics_server() {
	return PhysicsServer3D::get_singleton();
}

JoltPhysicsServer3D *PhantomJoint3D::_get_jolt_physics_server() {
	JoltPhysicsServer3D *physics_server = JoltPhysicsServer3D::get_singleton();

	if (unlikely(physics_server == nullptr)) {
		ERR_PRINT_ONCE(
				"PhantomJoint3D was unable to retrieve the Jolt-based physics server. "
				"Make sure that you have 'Jolt Physics (Extension)' set as the currently active "
				"physics engine. All Jolt-specific functionality related to joints will be ignored.");
	}

	return physics_server;
}

Transform3D PhantomJoint3D::_get_body_local_transform(const PhysicsBody3D &p_body) const {
	const Transform3D global_transform = get_global_transform().orthonormalized();
	const Transform3D body_global_transform = p_body.get_global_transform();
	const Transform3D body_global_transform_inv = body_global_transform.affine_inverse();
	const Transform3D body_local_transform = body_global_transform_inv * global_transform;

	return body_local_transform.orthonormalized();
}

void PhantomJoint3D::_notification(int32_t p_what) {
	Node3D::_notification(p_what);

	switch (p_what) {
		case NOTIFICATION_POST_ENTER_TREE: {
			_build();
		} break;

		case NOTIFICATION_EXIT_TREE: {
			_destroy();
		} break;

		default: {
		} break;
	}
}

void PhantomJoint3D::_body_exiting_tree() {
	_destroy();
}

void PhantomJoint3D::_connect_bodies() {
	PhysicsBody3D *body_a = get_body_a();
	PhysicsBody3D *body_b = get_body_b();

	static const StringName exit_signal("tree_exiting");

	const Callable exit_callable = callable_mp(this, &PhantomJoint3D::_body_exiting_tree);

	if (body_a != nullptr) {
		body_a->connect(exit_signal, exit_callable);
	}

	if (body_b != nullptr) {
		body_b->connect(exit_signal, exit_callable);
	}
}

void PhantomJoint3D::_disconnect_bodies() {
	PhysicsBody3D *body_a = get_body_a();
	PhysicsBody3D *body_b = get_body_b();

	static const StringName exit_signal("tree_exiting");

	const Callable exit_callable = callable_mp(this, &PhantomJoint3D::_body_exiting_tree);

	if (body_a != nullptr && body_a->is_connected(exit_signal, exit_callable)) {
		body_a->disconnect(exit_signal, exit_callable);
	}

	if (body_b != nullptr && body_b->is_connected(exit_signal, exit_callable)) {
		body_b->disconnect(exit_signal, exit_callable);
	}
}

bool PhantomJoint3D::_validate() {
	if (!is_inside_tree()) {
		return false;
	}

	PhysicsBody3D *body_a = get_body_a();
	PhysicsBody3D *body_b = get_body_b();

	const bool valid_node_a = !node_a.is_empty();
	const bool valid_node_b = !node_b.is_empty();

	const bool valid_body_a = body_a != nullptr;
	const bool valid_body_b = body_b != nullptr;

	String new_warning;

	if (valid_node_a && !valid_body_a) {
		new_warning = "Node A must be of type PhysicsBody3D";
	} else if (valid_node_b && !valid_body_b) {
		new_warning = "Node B must be of type PhysicsBody3D";
	} else if (!valid_node_a && !valid_node_b) {
		new_warning = "Joint does not connect any nodes";
	} else if (body_a == body_b) {
		new_warning = "Node A and Node B must be different nodes";
	}

	if (warning != new_warning) {
		warning = new_warning;
		_configuration_warnings_changed();
	}

	return warning.is_empty();
}

bool PhantomJoint3D::_configure() {
	if (!_validate()) {
		return false;
	}

	valid = true;

	PhysicsBody3D *body_a = get_body_a();
	PhysicsBody3D *body_b = get_body_b();

	if (body_a != nullptr) {
		_configure(body_a, body_b);
	} else if (body_b != nullptr) {
		_configure(body_b, nullptr);
	}

	return true;
}

bool PhantomJoint3D::_build() {
	if (!_configure()) {
		return false;
	}

	_update_enabled();
	_update_collision_exclusion();
	_update_velocity_iterations();
	_update_position_iterations();

	_connect_bodies();

	return true;
}

void PhantomJoint3D::_destroy() {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_disable_collisions_between_bodies(rid, false);
	physics_server->joint_clear(rid);

	_disconnect_bodies();

	valid = false;
}

void PhantomJoint3D::_update_enabled() {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_set_enabled(rid, enabled);
}

void PhantomJoint3D::_update_collision_exclusion() {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_disable_collisions_between_bodies(rid, collision_excluded);
}

void PhantomJoint3D::_update_solver_priority() {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_set_solver_priority(rid, solver_priority);
}

void PhantomJoint3D::_update_velocity_iterations() {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_set_solver_velocity_iterations(rid, velocity_iterations);
}

void PhantomJoint3D::_update_position_iterations() {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_set_solver_position_iterations(rid, position_iterations);
}

void PhantomJoint3D::_nodes_changing() {
	_destroy();
}

void PhantomJoint3D::_nodes_changed() {
	_build();
}

void PhantomJoint3D::_configuration_warnings_changed() {
	update_configuration_warnings();
}

void PhantomJoint3D::_enabled_changed() {
	_update_enabled();
}

void PhantomJoint3D::_collision_exclusion_changed() {
	_update_collision_exclusion();
}

void PhantomJoint3D::_solver_priority_changed() {
	_update_solver_priority();
}

void PhantomJoint3D::_velocity_iterations_changed() {
	_update_velocity_iterations();
}

void PhantomJoint3D::_position_iterations_changed() {
	_update_position_iterations();
}
