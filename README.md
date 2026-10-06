# Smart Delivery Planning – Fractional Knapsack (C Program)

A menu-driven C program implementing the **Fractional Knapsack Greedy Algorithm** to solve resource-allocation and delivery vehicle capacity optimization problems.

---

## 📌 Objectives
* Understand and implement the **Greedy Method**.
* Calculate the **Value/Weight ratio** for every package.
* Arrange packages in **decreasing order** of their Value/Weight ratio.
* Select complete packages whenever possible, and take a **fraction** of a package when required.
* Calculate and display the **maximum achievable value**.

---

## 🚀 Features & Menu Options
1. **Enter Package Details:** Input the number of packages, their individual values, weights, and the maximum carrying capacity of the delivery vehicle.
2. **Display Package Details:** View all packages in a tabular format.
3. **Calculate Value/Weight Ratio:** Automatically computes $\text{Ratio} = \text{Value} / \text{Weight}$ for each package.
4. **Sort Packages by Ratio:** Sorts the packages in decreasing order of their ratios using a greedy sorting approach.
5. **Find Maximum Value:** Runs the Fractional Knapsack algorithm to determine the optimal delivery contents and max value.
6. **Display Selected Packages:** Shows which packages (and what fractions of them) were picked for delivery.
7. **Exit:** Safely exit the program.

---

## 🧪 Illustrative Test Example

### Inputs:
* **Number of Packages:** `4`
* **Vehicle Capacity:** `15`
* **Package Details:**
  * Package 1: Value = `40`, Weight = `5`
  * Package 2: Value = `30`, Weight = `10`
  * Package 3: Value = `50`, Weight = `5`
  * Package 4: Value = `20`, Weight = `4`

### Expected Results:
* **Maximum Achievable Value:** `113.00`
* **Total Weight Used:** `15.00 / 15.00`
* **Selected Packages Breakdown:**
  * Package 3: `100%` taken (Value: 50, Weight: 5)
  * Package 1: `100%` taken (Value: 40, Weight: 5)
  * Package 4: `100%` taken (Value: 20, Weight: 4)
  * Package 2: `10%` taken (Fractional, Value: 3, Weight: 1)

---


# On Windows:
knapsack.exe
