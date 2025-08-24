# Prefer the object-oriented API (plt.subplots)
import numpy as np
import matplotlib.pyplot as plt
x = np.linspace(0, 2 * np.pi, 200) # x array with 200 points from 0 to 2π
y = np.sin(x) # y array with the sine of each x value
fig, ax = plt.subplots(figsize=(6, 3)) # Create a figure and axis with a specific size
ax.plot(x, y, lw=2) # Plot y vs x with a line width of 2
ax.set(title='Sine Wave', xlabel='Angle [rad]', ylabel='sin(x)') # Set title and labels
ax.grid(True, alpha=0.3) # Add a grid to the plot with a specific transparency
plt.show() # Display the plot
# Why: Getting fig, ax up front keeps code tidy and scales to multiple axes. Set labels/titles on the axes, not via plt.*


# Scatter plots with a colormap + colorbar (numeric feature as color)
rng = np.random.default_rng() # create a random number generator
x = rng.normal(size=300) # x array with 300 points from a normal distribution
y = 2*x + rng.normal(scale=0.8, size=300) # y array with a linear relation to x plus some noise
z = np.hypot(x, y) # z array with the magnitude/hypotenuse (distance from origin) for each (x, y) point

fig, ax = plt.subplots() # Create a figure and axis
sc = ax.scatter(x, y, c=z, cmap='viridis', alpha=0.8, s=28) # Create a scatter plot with color mapping
ax.set(title="Scatter with 3rd variable (color)", xlabel="X", ylabel="Y")
fig.colorbar(sc, ax=ax, label="||(x,y)||")
plt.show() # Display the plot
# Why: Encode a second/third numeric feature using color (c=) and add a colorbar for interpretability


# Histograms for distribution checks (bins, density, overlays)
rng2 = np.random.default_rng(42) # create another random number generator
data = rng2.normal(loc=0, scale=1.2, size=2000) # generate random data

fig, ax = plt.subplots() # Create a figure and axis
ax.hist(data, bins=40, density=True, alpha=0.6, label="Histogram (density)") # Create a histogram with density and 40 bins
# Overlay a smooth KDE-like line using a simple moving average of the hist heights
counts, edges = np.histogram(data, bins=80, density=True) # Get histogram data
centers = 0.5 * (edges[1:] + edges[:-1]) # Calculate bin centers
smooth = np.convolve(counts, np.ones(5)/5, mode='same') # Smooth the histogram counts
ax.plot(centers, smooth, lw=2, label="Smoothed density (approx.)") # Overlay the smoothed line
ax.set(title="Distribution Check", xlabel="Value", ylabel="Density")
ax.legend()
plt.show() # Display the plot
# Why: density=True normalizes counts. Overlays help you judge/skew heavy tails -- useful before model fitting


# Small multiples with shared axes (compare features side-by-side)
rng3 = np.random.default_rng(7) # create yet another random number generator
A = rng3.normal(loc=0, scale=1.0, size=500) # generate random data for A
B = rng3.normal(loc=1, scale=1.5, size=500) # generate random data for B
C = rng3.normal(loc=-0.5, scale=0.7, size=500) # generate random data for C

fig, axs = plt.subplots(1, 3, sharey=True, figsize=(9, 3)) # Create a figure with 3 subplots sharing the y-axis
for ax, data, name in zip(axs, [A, B, C], ["A", "B", "C"]):
    ax.boxplot(data, vert=True, widths=0.5) # Create a boxplot for each dataset
    ax.set(title=f"Feature {name}") # Set the title for each subplot
axs[0].set_ylabel("Value") # Set the y-label for the first subplot
fig.suptitle("Feature Comparison (shared y-axis)")
fig.tight_layout() # Adjust layout to prevent overlap
plt.show() # Display the plot
# Why: sharex/sharey keeps scales comparable across panels -- great for spotting distributional differences between features


# Clean exports for reports (tight layout, DPI, transparent bg)
x = np.linspace(0, 10, 200) # x array with 200 points from 0 to 10
y = np.log1p(x) + 0.2*np.sin(3*x) # y array with a log relation plus some sine variation

fig, ax = plt.subplots(figsize=(6, 3)) # Create a figure and axis with a specific size
ax.plot(x, y, lw=2) # Plot y vs x with a line width of 2
ax.set(title="Log-growth with ripple", xlabel="X", ylabel="Y") # Set titles and labels
fig.tight_layout() # Adjust layout to prevent overlap
fig.savefig("plot.svg", bbox_inches="tight") # Save the figure
plt.show() # Display the plot
# Why: tight_layout reduces clipping; dpi controls rasterization quality; SVG/PDF keep text crisp for docs/decks