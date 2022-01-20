using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using System.Diagnostics;
using System.Text;

public class Parse : MonoBehaviour
{
    public Solution Solution;
    public FacetRotations RubikRotations;
    
    private Process process;
    private StreamWriter messageStream;

    public Text TextDebug;

    private void Start()
    {
        process = null;
    }
    
    public void StartProcess()
    {
        try
        {
            if (!RubikRotations.IsRotationProcess())
            {
                process = new Process();

                process.StartInfo.FileName = Application.dataPath + "/../../rubik-solver";
                process.StartInfo.Arguments = ProcessArguments();

                process.EnableRaisingEvents = false;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.RedirectStandardInput = true;
                process.StartInfo.RedirectStandardError = true;

                process.OutputDataReceived += new DataReceivedEventHandler(DataReceived);
                process.ErrorDataReceived += new DataReceivedEventHandler(ErrorReceived);

                process.Start();

                process.BeginOutputReadLine();
            
                Invoke("test", 4.0f);
            }
        }
        catch (Exception e)
        {
            TextDebug.text = e.ToString();
            System.Console.WriteLine(e);
            throw;
        }
    }

    void test()
    { 
        messageStream = process.StandardInput;
        Solution.StartSolution();
        Invoke("StartSolution", 1.0f);
    }

    void StartSolution()
    {
        Solution.StartSolution();
    }

    string ProcessArguments()
    {
        string arguments = "";

        if (Solution.QueueSteps.Count > 0)
        {
            arguments += "\"" + Solution.QueueSteps.Dequeue();
        }
        
        while (Solution.QueueSteps.Count > 0)
        {
            arguments += " " + Solution.QueueSteps.Dequeue();
        }
        
        arguments += "\"";

        UnityEngine.Debug.Log("solver input: " + arguments);
        return arguments;
    }

    void DataReceived( object sender, DataReceivedEventArgs eventArgs )
    {
        if (eventArgs.Data != null)
        {
            string[] arguments = eventArgs.Data.ToString().Split(' ');
            
            UnityEngine.Debug.Log(arguments);
            
            foreach (string str in arguments)
            {
                if (str.Contains("2"))
                {
                    Solution.QueueSteps.Enqueue(str[0].ToString());
                    Solution.QueueSteps.Enqueue(str[0].ToString());
                }
                else
                    Solution.QueueSteps.Enqueue(str);
            }
            
            UnityEngine.Debug.Log(eventArgs.Data);
        }
    }
 
 
    void ErrorReceived( object sender, DataReceivedEventArgs eventArgs )
    {
        UnityEngine.Debug.LogError(eventArgs.Data);
        TextDebug.text = eventArgs.Data.ToString();
    }
}
