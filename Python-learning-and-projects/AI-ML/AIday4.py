# Train/test split + Pipeline keeps preprocesing and model together
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.datasets import make_classification

X, y = make_classification(n_samples=2000, n_features= 10, random_state=0) # x is features, y is target

Xtr, Xte, ytr, yte = train_test_split(X, y, test_size=0.2, stratify=y, random_state=0) # stratified split
clf = Pipeline([ # create a pipeline
    ("scale", StandardScaler()), # scaling
    ("lr", LogisticRegression(max_iter=1000)) # model
]).fit(Xtr, ytr) # fit the pipeline on training data

print("Test accuracy:", clf.score(Xte, yte)) # evaluate the pipeline on test data
# Why: Bundling steps prevents train/test leakage and makes deployment simple (clf.predict(...) does it all)


# Cross-Validation with stratification and custom scoring
from sklearn.model_selection import cross_val_score, StratifiedKFold
from sklearn.metrics import make_scorer, f1_score

cv = StratifiedKFold(n_splits=5, shuffle=True, random_state=0) # stratified k-fold
scores = cross_val_score(clf, X, y, cv=cv, scoring=make_scorer(f1_score)) # f1 scoring
print("F1 (cv):", scores.mean(), "±", scores.std()) # Printing the stratified kfold with mean scores and their std dist in f1 scoring
# Why: Stratification preserves class ratios; use metrics beyond accuracy (e.g. F1) when classes are imbalanced


# Mixed data: ColumnTransformer for numeric + categorical 
import numpy as np
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder
from sklearn.ensemble import RandomForestClassifier

# toy mixed matrix: 2 numerical + 1 categorical (strings)
X = np.array([[1.2, 5.0, "A"],
              [0.7, 3.1, "B"],
              [2.4, 9.0, "A"],
              [1.1, 4.2, "C"]], dtype=object) # 4D matrix for X
y = [0, 1, 0, 1] # 4 term vector for y

pre = ColumnTransformer([
    ("num", StandardScaler(), [0,1]), # Scaling
    ("cat", OneHotEncoder(handle_unknown='ignore'), [2]) # handle unknown categories
])

pipe = Pipeline([("pre", pre), ("rf", RandomForestClassifier(random_state=0))]).fit(X, y) # RandomForest model
print(pipe.predict([[1.0, 4.0, "A"]])) # printing predictions for new data
# Why: Apply different transforms per column type- clean, reproducible, no manual feature join hassles


# Hyperparamter search with GridSearchCV on a pipeline
from sklearn.model_selection import GridSearchCV
param_grid = {
    "rf__n_estimators": [100, 300], # Number of trees
    "rf__max_depth": [None, 8, 16] # Maximum depth
}
gs = GridSearchCV(pipe, param_grid, cv=3, n_jobs=-1, scoring="f1") # GridSearchCV initialization
gs.fit(X, y) # fitting the gridsearch

print("Best params:", gs.best_params_) # printing best parameters
best_model = gs.best_estimator_ # getting best model
# Why: Search space is defined on pipeline step names; CV happens with preprocessing inside the fold-- no leakage


# Save/Load models with joblib
import joblib

joblib.dump(best_model, "model.joblib") # saving the model
loaded = joblib.load("model.joblib") # loading the model
print(loaded.predict([[1.2, 5.5, "B"]])) # making predictions with the loaded model
# Apply: Persist the whole pipeline (preprocessing + estimator) for deployment or later reuse.