# AI/ML with Python — Day 2 (pandas data wrangling)
# Efficient reads: read_csv with usecols, dtype, parse_dates
import pandas as pd
from io import StringIO

csv = StringIO("""id,date,city,qty,price
1,2025-07-20,London,2,3.5
2,2025-07-21,Paris,1,4.0
3,2025-07-22,New York,5,2.5
""") # CSV data including sales records

df = pd.read_csv(csv, usecols=["id", "date", "city","qty","price"], dtype={"id": "int32", "city": "category", "qty": "int16", "price": "float32"}, parse_dates=["date"]) # Read CSV data into DataFrame
print(df.dtypes) # Print the data types of the DataFrame
# Why: Selecting columns and setting dtypes on read saves memory/time and gives correct types (e.g., datetime64[ns], category)


# Selection and safe assignment : .loc / .iloc & vectorized ops
# Vectorized column creation
df["revenue"] = df["qty"] * df["price"] # Create revenue column

# Boolean filter + assignment (avoid chained indexing)
mask = (df["city"] == "London") & (df["revenue"] < 8) # Create mask for low tier
df.loc[mask, "tier"] = "low" # Assign low tier
df.loc[~mask, "tier"] = "ok" # Assign ok tier

# Row/column selection
print(df.loc[df["city"] == "London", ["date", "revenue"]]) # Select rows for London and specific columns
print(df.iloc[:2, :3]) # Select first 2 rows and first 3 columns by position
# Why: .loc (label-based) and .iloc (position-based) are explicit and prevent the "chained assignment" pitfalls. Arithmetic is vectorized -- no loops


# Grouped aggregations (named agg) & transform
g = (df.groupby("city").agg(total_qty=("qty", "sum"), avg_price=("price", "mean"), orders=("id", "count")).reset_index()) # Group by city and aggregate 
print(g) # Print grouped DataFrame

# Broadcast per-group stats back to rows
df["city_avg_rev"] = df.groupby("city")["revenue"].transform("mean") # Assign average revenue per city to each row
print(df[["city","revenue","city_avg_rev"]]) # Print city, revenue, and city_avg_rev columns
# Why: groupby().agg() computes per-group summaries; transform() returns a same-length series for per-row features (great for ML feature engineering)


# Joins/merges with validation and indicators
cities = pd.DataFrame({"city": ["London", "Paris", "New York", "Berlin"], "country": ["UK", "France", "USA", "Germany"]}) # Create cities DataFrame

# Left join, assert one-to-one key relationship, show match status
joined = pd.merge(df, cities, on="city", how="left", validate="many_to_one", indicator=True) # Merge df with cities on city column
print(joined[["city", "country", "_merge"]]) # Print city, country, and _merge columns
# Why: merge supports SQL-like joins. Validate catches accidental duplicates; indicator shows matched/unmatched rows to debug joins


# Reshaping: pivot_table and melt
# Pivot: revenue by city x date, fill missing with 0, add row/col totals
pt = pd.pivot_table(df, values="revenue", index="city", columns="date", aggfunc="sum", fill_value=0, margins=True, margins_name="Total") # Create pivot table
print(pt) # Print pivot table

# long <-> wide reshaping
long = pd.melt(df, id_vars=["id","city"], value_vars=["qty", "price", "revenue"], var_name="metric", value_name="value") # Melt DataFrame to long format
print(long.head()) # Print first 5 rows of long DataFrame
# Why: Pivot tables create cross-tabs for quick reports/features; melt (unpivot) is key for tidy data formats and model-ready pipelines

