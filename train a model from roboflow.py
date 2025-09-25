# Install necessary packages
!pip install ultralytics roboflow -q

# Import libraries
from roboflow import Roboflow

# Initialize Roboflow with your API key
rf = Roboflow(api_key="YOUR_ROBOFLOW_API_KEY")

# Select your workspace, project, and dataset version
project = rf.workspace("your-workspace-name").project("your-project-name")
dataset = project.version(1).download("yolov8")

# Import Ultralytics YOLO for training
from ultralytics import YOLO

# Load a pretrained YOLOv8 model (YOLOv8s in this example)
model = YOLO("yolov8s.pt")

# Train the model with your Roboflow dataset
model.train(data=dataset.data.yaml, epochs=50, imgsz=640)
