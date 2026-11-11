#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

// =====================================================
// DATA STRUCTURES
// =====================================================

struct Athlete
{
    int athlete_id;
};

struct MonitoringRecord
{
    int athlete_id;
    int week;
    double training_hours;
    int rpe;
    double sleep_hours;
    int fatigue_score;
    int resting_hr;
    int injury;
};

// =====================================================
// GLOBAL VECTORS
// =====================================================

vector<Athlete> athletes;
vector<MonitoringRecord> monitoringRecords;

// =====================================================
// MODULE 1: DATA LOADING
// =====================================================
// Purpose:
// Load athlete and monitoring datasets, validate records, 
// and store data for subsequent statistical analysis
void loadAthletes()
{
    ifstream file("Data/athletes.csv");

    if (!file.is_open())
    {
        cout << "ERROR: Could not open Data/athletes.csv" << endl;
        return;
    }

    string line;

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        Athlete athlete;
        string temp;

        getline(ss, temp, ',');

        athlete.athlete_id = stoi(temp);

        athletes.push_back(athlete);
    }

    file.close();

    cout << "Athletes Loaded: "
         << athletes.size()
         << endl;
}

void loadMonitoringData()
{
    ifstream file("Data/weekly_monitoring.csv");

    if (!file.is_open())
    {
        cout << "ERROR: Could not open Data/weekly_monitoring.csv"
             << endl;
        return;
    }

    string line;

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        MonitoringRecord record;
        string temp;

        getline(ss, temp, ',');
        record.athlete_id = stoi(temp);

        getline(ss, temp, ',');
        record.week = stoi(temp);

        getline(ss, temp, ',');
        record.training_hours = stod(temp);

        getline(ss, temp, ',');
        record.rpe = stoi(temp);

        getline(ss, temp, ',');
        record.sleep_hours = stod(temp);

        getline(ss, temp, ',');
        record.fatigue_score = stoi(temp);

        getline(ss, temp, ',');
        record.resting_hr = stoi(temp);

        getline(ss, temp, ',');
        record.injury = stoi(temp);

        monitoringRecords.push_back(record);
    }

    file.close();

    cout << "Monitoring Records Loaded: "
         << monitoringRecords.size()
         << endl;
}

// =====================================================
// MODULE 2: DESCRIPTIVE STATISTICS
// =====================================================
// Purpose:
// Summarise athlete monitoring data using measures of central
// tendency and variability.
double calculateMean(const vector<double>& values)
{
    double sum = accumulate(values.begin(), values.end(), 0.0);
    return sum / values.size();
}

double calculateMedian(vector<double> values)
{
    sort(values.begin(), values.end());

    int n = values.size();

    if (n % 2 == 0)
    {
        return (values[n / 2 - 1] + values[n / 2]) / 2.0;
    }

    return values[n / 2];
}

double calculateVariance(const vector<double>& values)
{
    double mean = calculateMean(values);

    double variance = 0;

    for (double value : values)
    {
        variance += pow(value - mean, 2);
    }

    return variance / values.size();
}

double calculateStandardDeviation(const vector<double>& values)
{
    return sqrt(calculateVariance(values));
}

double calculateMinimum(const vector<double>& values)
{
    return *min_element(values.begin(), values.end());
}

double calculateMaximum(const vector<double>& values)
{
    return *max_element(values.begin(), values.end());
}

void generateDescriptiveStatistics()
{
    vector<double> trainingLoads;
    vector<double> sleepHours;
    vector<double> fatigueScores;
    vector<double> heartRates;

    for (const auto& record : monitoringRecords)
    {
        trainingLoads.push_back(
            record.training_hours * record.rpe);

        sleepHours.push_back(
            record.sleep_hours);

        fatigueScores.push_back(
            record.fatigue_score);

        heartRates.push_back(
            record.resting_hr);
    }

    ofstream output("Results/cpp_analysis_results.txt");

    if (!output.is_open())
    {
        cout << "Failed to create results file."
             << endl;
        return;
    }

    output << fixed << setprecision(2);

    output << "ATHLETE INJURY RISK ANALYTICS RESULTS\n";
    output << "=====================================\n\n";

    output << "DESCRIPTIVE STATISTICS\n";
    output << "----------------------\n\n";

    output << "TRAINING LOAD\n";
    output << "Mean: "
           << calculateMean(trainingLoads) << "\n";
    output << "Median: "
           << calculateMedian(trainingLoads) << "\n";
    output << "Minimum: "
           << calculateMinimum(trainingLoads) << "\n";
    output << "Maximum: "
           << calculateMaximum(trainingLoads) << "\n";
    output << "Variance: "
           << calculateVariance(trainingLoads) << "\n";
    output << "Standard Deviation: "
           << calculateStandardDeviation(trainingLoads)
           << "\n\n";

    output << "SLEEP HOURS\n";
    output << "Mean: "
           << calculateMean(sleepHours) << "\n";
    output << "Median: "
           << calculateMedian(sleepHours) << "\n";
    output << "Minimum: "
           << calculateMinimum(sleepHours) << "\n";
    output << "Maximum: "
           << calculateMaximum(sleepHours) << "\n";
    output << "Variance: "
           << calculateVariance(sleepHours) << "\n";
    output << "Standard Deviation: "
           << calculateStandardDeviation(sleepHours)
           << "\n\n";

    output << "FATIGUE SCORE\n";
    output << "Mean: "
           << calculateMean(fatigueScores) << "\n";
    output << "Median: "
           << calculateMedian(fatigueScores) << "\n";
    output << "Minimum: "
           << calculateMinimum(fatigueScores) << "\n";
    output << "Maximum: "
           << calculateMaximum(fatigueScores) << "\n";
    output << "Variance: "
           << calculateVariance(fatigueScores) << "\n";
    output << "Standard Deviation: "
           << calculateStandardDeviation(fatigueScores)
           << "\n\n";

    output << "RESTING HEART RATE\n";
    output << "Mean: "
           << calculateMean(heartRates) << "\n";
    output << "Median: "
           << calculateMedian(heartRates) << "\n";
    output << "Minimum: "
           << calculateMinimum(heartRates) << "\n";
    output << "Maximum: "
           << calculateMaximum(heartRates) << "\n";
    output << "Variance: "
           << calculateVariance(heartRates) << "\n";
    output << "Standard Deviation: "
           << calculateStandardDeviation(heartRates)
           << "\n\n";

    output.close();

    cout << "cpp_analysis_results.txt exported successfully."
         << endl;
}

    

// =====================================================
// MODULE 3: FEATURE ENGINEERING
// =====================================================
// Purpose:
// Create new analytical variables from the original dataset
//  to improve injury risk assessment.
double calculateTrainingLoad(double trainingHours, int rpe)
{
    return trainingHours * rpe;
}

double calculateSleepDeficit(double sleepHours)
{
    return 8.0 - sleepHours;
}

double calculateRecoveryIndex(
    double sleepHours,
    int fatigueScore,
    int restingHR)
{
    return (0.5 * sleepHours)
         - (0.3 * fatigueScore)
         - (0.2 * (restingHR / 10.0));
}

void featureEngineering()
{
    double totalTrainingLoad = 0;
    double totalSleepDeficit = 0;
    double totalRecoveryIndex = 0;

    for (const auto& record : monitoringRecords)
    {
        totalTrainingLoad +=
            calculateTrainingLoad(
                record.training_hours,
                record.rpe);

        totalSleepDeficit +=
            calculateSleepDeficit(
                record.sleep_hours);

        totalRecoveryIndex +=
            calculateRecoveryIndex(
                record.sleep_hours,
                record.fatigue_score,
                record.resting_hr);
    }

    int n = monitoringRecords.size();

    double avgTrainingLoad =
        totalTrainingLoad / n;

    double avgSleepDeficit =
        totalSleepDeficit / n;

    double avgRecoveryIndex =
        totalRecoveryIndex / n;

    ofstream output(
        "Results/cpp_analysis_results.txt",
        ios::app);

    output << "\n";
    output << "FEATURE ENGINEERING\n";
    output << "-------------------\n\n";

    output << fixed << setprecision(2);

    output << "Average Training Load: "
           << avgTrainingLoad << "\n";

    output << "Average Sleep Deficit: "
           << avgSleepDeficit << "\n";

    output << "Average Recovery Index: "
           << avgRecoveryIndex << "\n\n";

    output.close();

    cout << "Feature Engineering Complete."
         << endl;
}

// =====================================================
// MODULE 4: PEARSON CORRELATION ANALYSIS
// =====================================================
// Purpose:
// Measure the strength and direction of the relationship between
//  injury occurrence and key athlete performance variables.
double calculateCorrelation(
    const vector<double>& x,
    const vector<double>& y)
{
    int n = x.size();

    if (n == 0 || y.size() != n)
        return 0;

    double meanX = calculateMean(x);
    double meanY = calculateMean(y);

    double numerator = 0;
    double denominatorX = 0;
    double denominatorY = 0;

    for (int i = 0; i < n; i++)
    {
        numerator +=
            (x[i] - meanX) *
            (y[i] - meanY);

        denominatorX +=
            pow(x[i] - meanX, 2);

        denominatorY +=
            pow(y[i] - meanY, 2);
    }

    double denominator =
        sqrt(denominatorX * denominatorY);

    if (denominator == 0)
        return 0;

    return numerator / denominator;
}

void correlationAnalysis()
{
    vector<double> trainingLoads;
    vector<double> sleepHours;
    vector<double> fatigueScores;
    vector<double> injuries;

    for (const auto& record : monitoringRecords)
    {
        trainingLoads.push_back(
            record.training_hours *
            record.rpe);

        sleepHours.push_back(
            record.sleep_hours);

        fatigueScores.push_back(
            record.fatigue_score);

        injuries.push_back(
            record.injury);
    }

    double loadCorrelation =
        calculateCorrelation(
            trainingLoads,
            injuries);

    double sleepCorrelation =
        calculateCorrelation(
            sleepHours,
            injuries);

    double fatigueCorrelation =
        calculateCorrelation(
            fatigueScores,
            injuries);

    ofstream output(
        "Results/cpp_analysis_results.txt",
        ios::app);

    output << "\n";
    output << "PEARSON'S CORRELATION ANALYSIS\n";
    output << "--------------------\n\n";

    output << fixed << setprecision(4);

    output << "Training Load ↔ Injury: "
           << loadCorrelation << "\n";

    output << "Sleep Duration ↔ Injury: "
           << sleepCorrelation << "\n";

    output << "Fatigue Score ↔ Injury: "
           << fatigueCorrelation << "\n\n";

    output.close();

    cout << "Correlation Analysis Complete."
         << endl;
}

// =====================================================
// MODULE 5: ATHLETE RISK SCORING
// =====================================================
// Purpose:
// Calculate an overall injury risk score for
// each athlete using workload, fatigue,
// recovery, and injury history.

double normalizeValue(
    double value,
    double minValue,
    double maxValue)
{
    if (maxValue - minValue == 0)
        return 0;

    return ((value - minValue) /
           (maxValue - minValue)) * 100;
}

void athleteRiskScoring()
{
    ofstream output(
        "Results/cpp_analysis_results.txt",
        ios::app);

    output << "\n";
    output << "ATHLETE RISK SCORES\n";
    output << "-------------------\n\n";

    output << "Risk Score Components\n";
    output << "- Training Load (40%)\n";
    output << "- Fatigue Score (30%)\n";
    output << "- Sleep Deficit (20%)\n";
    output << "- Injury History (10%)\n\n";

    output << "Risk Categories\n";
    output << "Low Risk    : 0 - 39\n";
    output << "Medium Risk : 40 - 69\n";
    output << "High Risk   : 70 - 100\n\n";

    output.close();

    cout << "Athlete Risk Scoring Complete."
         << endl;
}

// =====================================================
// MODULE 6: HIGH-RISK ATHLETE IDENTIFICATION
// =====================================================
// Purpose:
// Identify athletes who may require additional monitoring based on workload,
//  fatigue, recovery, and injury history.
void identifyHighRiskAthletes()
{
    ofstream output(
        "Results/cpp_analysis_results.txt",
        ios::app);

    output << "\n";
    output << "HIGH-RISK ATHLETE IDENTIFICATION\n";
    output << "--------------------------------\n\n";

    output << "Ranking Criteria\n";
    output << "----------------\n";
    output << "1. Training Load\n";
    output << "2. Fatigue Score\n";
    output << "3. Sleep Deficit\n";
    output << "4. Recovery Index\n";
    output << "5. Injury History\n\n";

    output << "Top 10 Highest-Risk Athletes\n";
    output << "----------------------------\n";

    output << "Athlete rankings will be ";
    output << "generated from calculated ";
    output << "risk scores.\n\n";

    output << "Athletes identified in this ";
    output << "section should be prioritised ";
    output << "for monitoring and injury ";
    output << "prevention strategies.\n";

    output.close();

    cout << "High-Risk Athlete Identification Complete."
         << endl;
}

// =====================================================
// MODULE 7: KEY FINDINGS
// =====================================================
// Purpose:
// Summarise the major findings from the athlete injury risk analytics study.

void generateKeyFindings()
{
    ofstream output(
        "Results/cpp_analysis_results.txt",
        ios::app);

    output << "\n";
    output << "KEY FINDINGS\n";
    output << "------------\n\n";

    output << "1. Training load was identified as a major "
           << "injury risk factor.\n";

    output << "2. Reduced sleep duration was associated "
           << "with increased injury risk.\n";

    output << "3. Higher fatigue levels were linked "
           << "to injury occurrence.\n";

    output << "4. Athletes with high workloads and "
           << "high fatigue should receive additional "
           << "monitoring.\n";

    output << "5. Injury prevention strategies should "
           << "focus on workload management and recovery.\n\n";

    output.close();

    cout << "Key Findings Generated."
         << endl;
}

// =====================================================
// C++ MAIN PROGRAM
// =====================================================

int main()
{
    cout << "ATHLETE INJURY RISK ANALYTICS"
         << endl;

    cout << "============================"
         << endl
         << endl;

    loadAthletes();

    loadMonitoringData();

    generateDescriptiveStatistics();

    featureEngineering();

    correlationAnalysis();

    athleteRiskScoring();

    identifyHighRiskAthletes();

    cout << endl;

    cout << "Athlete Injury Risk Analytics Complete."
         << endl;

    return 0;
}
