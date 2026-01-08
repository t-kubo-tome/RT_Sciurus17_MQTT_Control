from pathlib import Path
import sys

import numpy as np

src_path = Path(__file__).parent.parent
sys.path.insert(0, str(src_path))

from sciurus.sciurus_robot import SciurusRobot


if __name__ == "__main__":
    robot = SciurusRobot()
    print(f"{robot.connect()=}")
    print(f"{robot.enable()=}")
    print(f"{robot.get_current_joint()=}")
    joint = robot.get_current_joint()
    joint = (np.array(joint) + np.array([0, 0, 0, 0, 0, 5])).tolist()
    print(f"{robot.move_joint(joint)=}")
    print(f"{robot.get_current_joint()=}")
    print(f"{robot.disable()=}")
    print(f"{robot.disconnect()=}")    
