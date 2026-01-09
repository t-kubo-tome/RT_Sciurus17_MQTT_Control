from sciurus_robot import SciurusRobot


if __name__ == "__main__":
    robot = SciurusRobot()
    print(f"{robot.connect()=}")
    print(f"{robot.enable()=}")
    print(f"{robot.get_current_joint()=}")
    default_joints_groups = {
        "right_arm": [-0.00920388, -1.57233, -0.00153398, 2.72742, -0.00306796, -2.08468, -0.00153398],
        "right_hand": [0.00153398],
        "left_arm": [0.0076699, 1.5708, 0, -2.71668, -0.0076699, 2.09082, -0.00153398],
        "left_hand": [0.00153398],
        "torso": [0.00153398, -0.00153398, -0.00306796],
    }
    joint = []
    for k, v in default_joints_groups.items():
        joint.extend(v)
    print(f"{robot.move_joint(joint)=}")
    print(f"{robot.get_current_joint()=}")
    print(f"{robot.disable()=}")
    print(f"{robot.disconnect()=}")
 
