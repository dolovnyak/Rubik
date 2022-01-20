using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Solution : MonoBehaviour
{
    public Queue<string> QueueSteps;
    
    private FacetRotations _rubikRotations;

    private bool _solution = false;
    private string _stepsString;

    private void Start()
    {
        QueueSteps = new Queue<string>();
        _rubikRotations = GetComponent<FacetRotations>();
    }

    public void StartSolution()
    {
        if (!_solution)
        {
            _solution = true;

            _stepsString = string.Empty;

            NextStep();
        }
    }

    public bool IsSolution()
    {
        return _solution;
    }

    public void NextStep()
    {
        if (!_rubikRotations.IsRotationProcess())
        {
            if (QueueSteps.Count > 0)
            {
                ChangeFacetRotate(QueueSteps.Dequeue());
            }
            else
            {
                _solution = false;
                Debug.Log(_stepsString);
            }
        }
        else
        {
            Invoke("NextStep", 0.1f);
        }
    }

    public void AddStep(string nameStep)
    {
        QueueSteps.Enqueue(nameStep);
    }
    
    void ChangeFacetRotate(string nameRotate)
    {
        if (nameRotate == "F")
        {
            _rubikRotations.FacingRight(Vector3.right, -1, new Vector3(1, 0, 1));
            _stepsString += "F ";
        }
        else if (nameRotate == "F'")
        {
            _rubikRotations.FacingRight(Vector3.right, 1, new Vector3(1, 0, 1));
            _stepsString += "F' ";
        }

        else if (nameRotate == "B")
        {
            _rubikRotations.FacingRight(Vector3.right, 1, new Vector3(1, 0, -1));
            _stepsString += "B ";
        }
        else if (nameRotate == "B'")
        {
            _rubikRotations.FacingRight(Vector3.right, -1, new Vector3(1, 0, -1));
            _stepsString += "B' ";
        }

        else if (nameRotate == "R")
        {
            _rubikRotations.FacingForward(Vector3.right, 1, new Vector3(1, 0, 1));
            _stepsString += "R ";
        }
        else if (nameRotate == "R'")
        {
            _rubikRotations.FacingForward(Vector3.right, -1, new Vector3(1, 0, 1));
            _stepsString += "R' ";
        }

        else if (nameRotate == "L")
        {
            _rubikRotations.FacingForward(Vector3.right, -1, new Vector3(-1, 0, 1));
            _stepsString += "L ";
        }
        else if (nameRotate == "L'")
        {
            _rubikRotations.FacingForward(Vector3.right, 1, new Vector3(-1, 0, 1));
            _stepsString += "L' ";
        }

        else if (nameRotate == "U")
        {
            _rubikRotations.FacingForward(Vector3.up, 1, new Vector3(0, 1, 1));
            _stepsString += "U ";
        }
        else if (nameRotate == "U'")
        {
            _rubikRotations.FacingForward(Vector3.up, -1, new Vector3(0, 1, 1));
            _stepsString += "U' ";
        }

        else if (nameRotate == "D")
        {
            _rubikRotations.FacingForward(Vector3.up, -1, new Vector3(0, -1, 1));
            _stepsString += "D ";
        }
        else if (nameRotate == "D'")
        {
            _rubikRotations.FacingForward(Vector3.up, 1, new Vector3(0, -1, 1));
            _stepsString += "D' ";
        }
        else 
        {
            Debug.LogError("error: \"" + nameRotate + "\"");
        }
    }
}
