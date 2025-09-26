from ultralytics import YOLO

# Path to your ONNX model weights file
model_path = r"D:\college\S5 STUFFS\ML\ml project\SNAPMEAL\best (1).onnx"

# Load YOLO model from ONNX weights
model = YOLO(model_path)

# Path to input image for prediction - must be a file, not folder
image_path = r"D:\college\S5 STUFFS\ML\ml project\SNAPMEAL"  # Update with your image file

# Perform inference on the image with confidence threshold 0.5 and save results
results = model.predict(image_path, save=True, conf=0.60)

# Show detected results (bounding boxes, labels)
results[0].show()

# Get detected class names from results
detected_classes = results[0].names  # Dictionary mapping class indices to names
boxes = results[0].boxes  # Detected bounding boxes

print("Objects detected:")

# For each detected box, print class name and confidence
for box in boxes:
    cls_id = int(box.cls[0])  # Class index
    conf = box.conf[0]        # Confidence score
    class_name = detected_classes[cls_id]
    print(f" - {class_name} with confidence {conf:.2f}")

