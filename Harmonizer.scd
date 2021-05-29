(
s.boot; //boot server
OSCFunc.trace(true, false); /*in order to know on which port JUCE is sending OSC packets, please execute this block, try to change the knobs  and copy the recieving port in netAddr "port" argument */
)


//Network address definition: IP & port from where we're listening. The port X is the port the other application is sending from, not the port SC is receiving on.
n=NetAddr("127.0.0.1", 55576);



//Synthdef allowing the input signal retrieval.
(
SynthDef.new(\mic, {
	arg in=0, out=0, amp=1;
	var sig;
	sig = SoundIn.ar(in!2)*amp;
	Out.ar(out, sig);

}).add;
)

//HARMONIZER
(
SynthDef.new(\harm, {



	arg in, amp=2, pitch1=0, pitch2=0, pitch3=0, detune=1, blend=0.5, vol1=0, vol2=0, vol3=0, reverb=0;
    var out = 0, out1 = 0, out2 = 0, out3 = 0, sig = 0;


	sig = In.ar(in, 2);// input bus of harm == output bus of mic


	out1 = PitchShift.ar(
        sig,    // stereo audio input
        0.1,             // grain size
		(1 + (pitch1/4))*detune, // pitch ratio
        0,                 // pitch dispersion
        0.004            // time dispersion
    );



	out2 = PitchShift.ar(
        sig,    // stereo audio input
        0.1,             // grain size
		(1 + (pitch2/4))*detune,//pitch ratio
        0,                 // pitch dispersion
        0.004            // time dispersion
    );





	out3 = PitchShift.ar(
        sig,    // stereo audio input
        0.1,             // grain size
		(1 + (pitch3/4))*detune,//pitch ratio
        0,                 // pitch dispersion
        0.004            // time dispersion
    );

//harmonized out = sum of three voice lines
	out = (out1*vol1) + (out2*vol2) + (out3*vol3);
//overall output: mix of reverbered harmonized line times wet, original signal times dry. everything multiplied by general amplitude
	out = Mix([(FreeVerb.ar(out,room:reverb)*blend), (sig*(1-blend))]) * amp;

//pass out to the output busses
	Out.ar(0, out);



}).add;
);




 //SYNTHS ALLOCATION AND GLOBAL VARIABLES, GROUPS DECLARATION
(

~cBus = Bus.audio(s, 2);

~micGrp = Group.new;

//KEYWORD AFTER NECESSARY TO PROCESS DATA AFTER IT HAS BEEN TAKEN FROM MIC

~efGrp= Group.after(~micGrp):

//SYNTH ALLOCATIONS

m = Synth(\mic, [\out, ~cBus ], ~micGrp);

e = Synth(\harm, [\in, ~cBus], ~efGrp);


);


//OSC COMMUNICATION
(
//receipt of amp value from juce's knob with parameter ID "output"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\amp, msg[1]); msg[1].postln}, '/output', n);
//receipt of detune value from juce's knob with parameter ID "output"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\detune, msg[1]); msg[1].postln}, '/detune', n);
//receipt of blend value from juce's knob with parameter ID "blend"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\blend, msg[1]); msg[1].postln}, '/blend', n);
//receipt of reverb value from juce's knob with parameter ID "reverb"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\reverb, msg[1]); msg[1].postln}, '/reverb', n);
//receipt of pitch1 value from juce's knob with parameter ID "voice1"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\pitch1, msg[1]); msg[1].postln}, '/voice1', n);
//receipt of pitch2 value from juce's knob with parameter ID "voice2"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\pitch2, msg[1]); msg[1].postln}, '/voice2', n);
//receipt of pitch3 value from juce's knob with parameter ID "voice3"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\pitch3, msg[1]); msg[1].postln}, '/voice3', n);
//receipt of vol1 value from juce's knob with parameter ID "vol_v1"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\vol1, msg[1]); msg[1].postln}, '/vol_v1', n);
//receipt of vol2 value from juce's knob with parameter ID "vol_v2"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\vol2, msg[1]); msg[1].postln}, '/vol_v2', n);
//receipt of vol3 value from juce's knob with parameter ID "vol_v3"
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\vol3, msg[1]); msg[1].postln}, '/vol_v3', n);

)

//TouchOSC interface

(
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\amp, msg[1]); msg[1].postln}, '/harm/output', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\detune, msg[1]); msg[1].postln}, '/harm/detune', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\blend, msg[1]); msg[1].postln}, '/harm/blend', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\reverb, msg[1]); msg[1].postln}, '/harm/reverb', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\pitch1, msg[1]); msg[1].postln}, '/harm/voice1', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\pitch2, msg[1]); msg[1].postln}, '/harm/voice2', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\pitch3, msg[1]); msg[1].postln}, '/harm/voice3', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\vol1, msg[1]); msg[1].postln}, '/harm/vol1', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\vol2, msg[1]); msg[1].postln}, '/harm/vol2', n);
OSCFunc.newMatching({ |msg, time, addr, recvPort| e.set(\vol3, msg[1]); msg[1].postln}, '/harm/vol3', n);


)

 