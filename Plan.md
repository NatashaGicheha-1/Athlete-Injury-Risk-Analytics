# Project plan
## Structure

```text
Athlete-Injury-Risk-Analytics/

├── Data/
│   ├── athletes.csv
│   └── weekly_monitoring.csv
│
├── Analysis.sql
│
├── Analysis.cpp
│
├── Results/
│   ├── descriptive_statistics.txt
│   ├── correlation_results.txt
│   ├── athlete_risk_scores.csv
│   └── key_findings.txt
│
├── Visualizations/
├── Presentation.pptx
├── Research.docs
└── README.md
```

## C++
| Module | Purpose | Output |
|----------|----------|----------|
| **Module 1: Data Loading** | Load athlete and monitoring datasets. Validate and store data for analysis. | Data structures populated with athlete and monitoring records. |
| **Module 2: Descriptive Statistics** | Calculate summary statistics for Training Load, Sleep Duration, Fatigue Score, and Resting Heart Rate. | `descriptive_statistics.txt` |
| **Module 3: Feature Engineering** | Generate new variables including Training Load, BMI, Sleep Deficit, and Recovery Index. | Engineered analytical features dataset. |
| **Module 4: Correlation Analysis** | Determine relationships between Training Load, Sleep, Fatigue, Age, Experience, and Injury occurrence. | `correlation_results.txt` |
| **Module 5: Athlete Risk Scoring** | Calculate injury risk scores and classify athletes into Low, Medium, and High Risk categories. | `athlete_risk_scores.csv` |
| **Module 6: High-Risk Athlete Identification** | Identify athletes requiring the most monitoring based on workload, fatigue, sleep, and injury history. | Ranked list of high-risk athletes. |
| **Module 7: Results Export** | Export descriptive statistics, correlation results, athlete risk scores, and key findings. | `descriptive_statistics.txt`, `correlation_results.txt`, `athlete_risk_scores.csv`, `key_findings.txt` |
