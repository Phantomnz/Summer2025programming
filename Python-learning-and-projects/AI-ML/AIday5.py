# AI/ML with Python — Day 5 (final) (Deep learning quick start: TensorFlow & PyTorch)
# Tensorflow/keras: a tiny MLP (Meaning Multi-Layer Perceptron) classifier
import tensorflow as tf
from sklearn.datasets import make_moons
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
X, y = make_moons(n_samples=2000, noise=0.2, random_state=0) # Generate synthetic dataset
X = StandardScaler().fit_transform(X) # Standardize features
Xtr, Xte, ytr, yte = train_test_split(X, y, test_size=0.2, random_state=0) # Split into train/test sets

model = tf.keras.Sequential([ # Define a sequential model
    tf.keras.Input(shape=(2,)), # Input layer
    tf.keras.layers.Dense(16, activation='relu'), # Hidden layer with ReLU activation (ReLU is a popular activation function for hidden layers)
    tf.keras.layers.Dense(1, activation='sigmoid') # Output layer with sigmoid activation (sigmoid activation is used for binary classification)
])
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy']) # Compile the model with Adam optimizer and binary crossentropy loss
model.fit(Xtr, ytr, epochs=20, batch_size=32, verbose=0) # Train the model
print("TF test acc:", model.evaluate(Xte, yte, verbose=0)[1]) # Evaluate the model on test data
# Why: Sequential + dense layers gives a quick baseline; Use standardized inputs and a suitable loss classification


# Keras callbacks: early stopping & best-weights checkpoint
cb = [ 
    tf.keras.callbacks.EarlyStopping(patience=5, restore_best_weights=True), # Stop training when the validation loss is not decreasing
    tf.keras.callbacks.ModelCheckpoint("best_model.h5", save_best_only=True) # Save the best model
]
model.fit(Xtr, ytr, epochs=100, batch_size=32, validation_split=0.2, callbacks=cb, verbose=0) # Train the model with validation split and callbacks
# Why: Prevent overfitting and automatically keep the best model during training


# Pytorch: define a model and a training step
import torch, torch.nn as nn, torch.optim as optim
from sklearn.datasets import make_regression
import numpy as np

X, y = make_regression(n_samples=2000, n_features=5, noise=10.0, random_state=0) # Generate synthetic regression dataset
Xtrain, Xtest, ytrain, ytest = train_test_split(X, y, test_size=0.2, random_state=0) # Split into train/test sets
device = torch.device("cuda" if torch.cuda.is_available() else "cpu") # Use GPU if available

Xtr_t = torch.tensor(Xtrain, dtype=torch.float32).to(device) # Convert training features to tensor
ytr_t = torch.tensor(ytrain, dtype=torch.float32).unsqueeze(1).to(device) # Convert training targets to tensor
Xte_t = torch.tensor(Xtest, dtype=torch.float32).to(device) # Convert test features to tensor
yte_t = torch.tensor(ytest, dtype=torch.float32).unsqueeze(1).to(device) # Convert test targets to tensor

net = nn.Sequential( # Define a sequential model
    nn.Linear(5,32), nn.ReLU(), # Hidden layer with ReLU activation
    nn.Linear(32, 1) # Output layer
).to(device) # Move model to device

opt = optim.Adam(net.parameters(), lr=1e-3) # Adam optimizer
loss_fn = nn.MSELoss() # Mean Squared Error loss

for _ in range(200):
    opt.zero_grad() # Zero the gradients
    loss = loss_fn(net(Xtr_t), ytr_t) # Compute the loss
    loss.backward() # Backpropagate the loss
    opt.step() # Update the weights

with torch.no_grad(): # No gradient computation for evaluation
    mse = loss_fn(net(Xte_t), yte_t).item() # Compute test loss
print("Torch test MSE:", round(mse, 3))
# Why: Minimal end-to-end regression loop: tensors -> model -> optimizer -> train -> evaluate; Uses GPU if available


# Data loaders & patching (PyTorch)
from torch.utils.data import DataLoader, TensorDataset

ds = TensorDataset(Xtr_t, ytr_t) # Create a dataset from tensors
loader = DataLoader(ds, batch_size=64, shuffle=True) # Create a data loader

for epoch in range(5): # Training loop
    for xb, yb in loader:
        opt.zero_grad() # Zero the gradients
        loss = loss_fn(net(xb), yb) # Compute the loss
        loss.backward() # Backpropagate the loss
        opt.step() # Update the weights
# Why: Mini-batches stabilize and speed training; DataLoader also makes shuffling and augmentation easy


# Save/load models (both frameworks)
# Tensorflow
model.save("tf_model.keras") # Save the model
loaded_tf = tf.keras.models.load_model("tf_model.keras") # Load the model

# PyTorch
torch.save(net.state_dict(), "torch_model.pt") # Save the model state dict
net2 = nn.Sequential( # Define a new model
    nn.Linear(5,32), nn.ReLU(), # Hidden layer with ReLU activation
    nn.Linear(32, 1) # Output layer
).to(device) # Move model to device
net2.load_state_dict(torch.load("torch_model.pt", map_location=device)) # Load the model state dict 
net2.eval() # Set the model to evaluation mode
# Why: Persisting models is essential for deployment, sharing and reproducibility