using System.Collections;
using System.Collections.Generic;
using UnityEngine;
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

    private void Start()
    {
        process = null;
    }
    
    // void StartProcess()
    // {
    //     if (!RubikRotations.IsRotationProcess())
    //     {
    //         try
    //         {
    //             process = new Process();
    //             process.EnableRaisingEvents = false;
    //             process.StartInfo.FileName = Application.dataPath + "/../../a.out";
    //             process.StartInfo.Arguments = ProcessArguments();
    //             process.StartInfo.UseShellExecute = false;
    //             process.StartInfo.RedirectStandardOutput = true;
    //             process.StartInfo.RedirectStandardInput = true;
    //             process.StartInfo.RedirectStandardError = true;
    //             process.OutputDataReceived += new DataReceivedEventHandler( DataReceived );
    //             process.ErrorDataReceived += new DataReceivedEventHandler( ErrorReceived );
    //             process.Start();
    //             process.BeginOutputReadLine();
    //             messageStream = process.StandardInput;
    //    
    //             UnityEngine.Debug.Log( "Successfully launched app" );
    //         }
    //         catch( Exception e )
    //         {
    //             UnityEngine.Debug.LogError( "Unable to launch app: " + e.Message );
    //         }
    //     }
    // }
    
    public void StartProcess()
    {
        if (!RubikRotations.IsRotationProcess())
        {
            process = new Process();

            process.StartInfo.FileName = Application.dataPath + "/../../rubik_solver/rubik-solver";
            // process.StartInfo.FileName = Application.dataPath + "/../../a.out";
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
            
            Invoke("test", 5.0f);
            // process.BeginOutputReadLine();
            // messageStream = process.StandardInput;

            // Solution.StartSolution();
            // Invoke("StartSolution", 3.0f);
        }
    }

    void test()
    {

            UnityEngine.Debug.LogError("Hui3");
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

        UnityEngine.Debug.Log("aaa: " + arguments);
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
    }
}
